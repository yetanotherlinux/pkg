add_executable(pkg
        main
        Account
        Args
        Exception
        Log
        Package
        PackageGraph
        PackageMetadata
        Settings
        Substitution
        infrastructure/Archive
        infrastructure/FileSystem
        infrastructure/Shell
        infrastructure/WebClient
        actions/Action
        actions/ActionFactory
        actions/BuildAction
        actions/CommandAction
        actions/FetchAction
        actions/IAction
        actions/InstallAction
        actions/StatusAction
        actions/UpdateAction
        storage/BuildStorage
        storage/HostStorage
        storage/MetadataStorage
        storage/PackageStorage
        storage/SourceStorage
        storage/Storage)

target_link_libraries(pkg archive curl json stdc++fs)

install(TARGETS pkg DESTINATION bin)
