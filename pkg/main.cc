#include "pkg/Args.h"
#include "pkg/Exception.h"
#include "pkg/PackageGraph.h"
#include "pkg/actions/ActionFactory.h"
#include "pkg/storage/HostStorage.h"
#include "pkg/storage/MetadataStorage.h"

using namespace pkg;
using pkg::actions::ActionFactory;
using pkg::storage::HostStorage;
using pkg::storage::MetadataStorage;

const std::string_view AppPath{"/etc/pkg"};
const std::string_view DefaultAction{"status"};
const std::string_view RequiredPackageName{"@environment"};

std::vector<std::string> GetPackages(const Args &args, const std::shared_ptr<HostStorage> &hostStorage) {
    std::vector<std::string> packageNames{args.GetPackages()};
    return packageNames.empty() ? hostStorage->GetPackages() : packageNames;
}

int main(int argc, char **argv) {
    const Log log{};
    const FileSystem fileSystem{};
    const WebClient webClient{};
    const Settings settings{std::string(AppPath), fileSystem};
    const Args args{argc, argv, std::string(DefaultAction)};

    auto metadataStorage{std::make_shared<MetadataStorage>(settings, webClient)};
    auto sourceStorage{std::make_shared<SourceStorage>(settings, fileSystem)};
    auto buildStorage{std::make_shared<BuildStorage>(settings, fileSystem)};
    auto packageStorage{std::make_shared<PackageStorage>(settings, fileSystem)};
    auto hostStorage{std::make_shared<HostStorage>(std::string(RequiredPackageName), settings, fileSystem)};

    Substitution substitution{settings.GetSubstitutions()};
    const ActionFactory actionFactory{
            sourceStorage, buildStorage, packageStorage, substitution, fileSystem, webClient, settings, log
    };
    const std::shared_ptr<IAction> action{actionFactory.CreateAction(args.GetAction())};
    if (!action) {
        log.Error() << "Invalid action '" << args.GetAction() << "'" << std::endl;
        for (const std::string &act : actionFactory.GetActions()) {
            log.Error() << '\t' << act << std::endl;
        }
        return EXIT_FAILURE;
    }


    const std::vector<std::string> packageNames{GetPackages(args, hostStorage)};
    if (packageNames.empty()) {
        log.Error() << "Packages are not specified" << std::endl;
        return EXIT_FAILURE;
    }

    PackageGraph packageGraph{metadataStorage};
    for (const std::string &packageName : packageNames) {
        packageGraph.Add(packageName);
    }
    while (!packageGraph.IsEmpty()) {
        PackageMetadata package{packageGraph.ExtractLeaf()};
        action->Perform(package, false);
    }

    if (args.HasForceFlag()) {
        for (const std::string &packageName : packageNames) {
            PackageMetadata package{metadataStorage->GetPackageMetadata(packageName)};
            action->Perform(package, true);
        }
    }

    return EXIT_SUCCESS;
}
