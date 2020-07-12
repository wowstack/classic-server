# Change log

This list contains all the changes which went into the project, including issues
and further references.

Items starting with `DEPRECATION` are important deprecation notices.

## Unreleased

-   [Added] platform abstraction library
-   [Changed] to recastnavigation commit 57610fa
-   [Changed] to use Docker image version 2.1.1
-   [Added] StormLib to vendored libraries
-   [Fixed] Drone build
    This allows to build and test with <https://docs.drone.io/quickstart/cli/>
-   [Improved] repository configuration
-   [Removed] old build status
-   [Changed] to always use latest build environment
-   [Improved] documentation
-   [Improved] README
-   [Changed] Patreon link to actionable URL
-   [Added] Drone build cache
-   [Added] missing parts to install directives
-   [Improved] Drone pipeline
-   [Added] AppVeyor configuration
    This adds Windows builds on AppVeyor.com.
-   [Added] Travis CI configuration
    This adds builds on the Open Source version of Travis CI.
-   [Added] Drone CI configuration
    This enables builds on a self-hosted Drone CI instance, allowing us to
    spin up as many builds as we want.
-   [Added] build system
    -   [Added] generic CMake project framework for cross-platform
    -   [Added] vendor libraries
    -   [Added] g3d library
    -   [Added] googletest library
    -   [Added] MPQ library
    -   [Added] recastnavigation library
    -   [Added] utf8cpp library
-   [Added] code style setting for clang-format
-   [Added] initial project documentation
-   [Added] issue and pull request templates
-   [Added] initial repository
    This initializes just to a blank project.
