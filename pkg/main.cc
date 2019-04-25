#include "pkg/Args.h"
#include "pkg/PackageGraph.h"
#include "pkg/actions/ActionFactory.h"
#include "pkg/storage/HostStorage.h"
#include "pkg/storage/MetadataStorage.h"

using namespace pkg;
using pkg::actions::ActionFactory;
using pkg::storage::HostStorage;
using pkg::storage::MetadataStorage;

std::vector<std::string> GetPackages(const Args &args, const std::shared_ptr<HostStorage> &hostStorage) {
    std::vector<std::string> packageNames{args.GetPackages()};
    return packageNames.empty() ? hostStorage->GetPackages() : packageNames;
}

int main(int argc, char **argv) {
    const Log log;
    const Settings settings{};
    const Args args{argc, argv, settings};

    const FileSystem fileSystem{};
    const WebClient webClient{};
    const Shell shell{settings};
    std::shared_ptr<MetadataStorage> metadataStorage{std::make_shared<MetadataStorage>(settings, webClient)};
    std::shared_ptr<SourceStorage> sourceStorage{std::make_shared<SourceStorage>(settings, fileSystem)};
    std::shared_ptr<BinaryStorage> binaryStorage{std::make_shared<BinaryStorage>(settings, fileSystem)};
    std::shared_ptr<PackageStorage> packageStorage{std::make_shared<PackageStorage>(settings, fileSystem)};
    std::shared_ptr<HostStorage> hostStorage{std::make_shared<HostStorage>(settings, fileSystem)};

    const ActionFactory actionFactory{
            sourceStorage, binaryStorage, packageStorage, fileSystem, webClient, shell, settings, log
    };
    const std::shared_ptr<IAction> action{actionFactory.CreateAction(args.GetAction())};
    if (!action) {
        log.Error() << "Invalid action '" << args.GetAction() << "'" << std::endl;
        for (const std::string_view &act : actionFactory.GetActions()) {
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
        action->Perform(package);
    }
    return EXIT_SUCCESS;
}
