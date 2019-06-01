add_executable(pkg
        main
        Args
        Exception
        Log
        Package
        PackageGraph
        PackageMetadata
        Settings
        Substitution
        actions/Action
        actions/ActionFactory
        actions/BuildAction
        actions/CommandAction
        actions/FetchAction
        actions/IAction
        actions/InstallAction
        actions/StatusAction
        actions/UpdateAction
        infrastructure/Account
        infrastructure/Archive
        infrastructure/FileSystem
        infrastructure/Kernel
        infrastructure/Shell
        infrastructure/WebClient
        storage/BuildStorage
        storage/HostStorage
        storage/MetadataStorage
        storage/PackageStorage
        storage/SourceStorage
        storage/Storage)

target_link_libraries(pkg archive curl json stdc++fs)

install(TARGETS pkg DESTINATION bin)
