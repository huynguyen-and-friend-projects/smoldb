# Set up development environment

<!--toc:start-->
- [Set up development environment](#set-up-development-environment)
  - [The lazy way](#the-lazy-way)
  - [The normal way](#the-normal-way)
    - [Unix systems](#unix-systems)
    - [For Windows system](#for-windows-system)
      - [Way 1](#way-1)
      - [Way 2](#way-2)
<!--toc:end-->

- There are 2 ways, the "lazy" way and the "normal" way.

## The lazy way

> [!IMPORTANT]
> Make sure you have Docker Engine and/or Docker Desktop installed
> [follow the documentation](https://docs.docker.com/engine/install/)

- For more detail, follow [the documentation from Visual Studio Code themselves](https://code.visualstudio.com/docs/devcontainers/containers).
- This is applicable to Visual Studio Code ~~snobs~~ users, and works on any platform.

1. Install the Docker and Dev Container extensions.
2. Run the dev container. The Dockerfile used is [this one](../.devcontainer/Dockerfile).
3. Wait for the image to build.
 The image will also configure CMake to setup build system for a Linux debug version using clang.

> [!IMPORTANT]
> When you exit the dev container, be sure to re-configure CMake build (with the convenience script). If you're on Windows, use git bash
>
> ```bash
> ./cmake-default-init.sh
> ```
>

## The normal way

### Unix systems

- Download the following:
  - git, obviously.
  - cmake
  - ninja
  - clang or gcc. Preferably clang
  - clang-tools-extra, or clang-tools on Debian systems
  - valgrind; optional, if on Linux
  - docker. [Follow the documentation](https://docs.docker.com/engine/install/)

```bash
# for debian
sudo apt-get update
sudo apt-get install -y git clang clang-tools cmake ninja-build valgrind

# copied from Docker documentation
sudo apt-get install ca-certificates curl
sudo install -m 0755 -d /etc/apt/keyrings
sudo curl -fsSL https://download.docker.com/linux/debian/gpg -o /etc/apt/keyrings/docker.asc
sudo chmod a+r /etc/apt/keyrings/docker.asc
# Add the repository to Apt sources:
# Replace $VERSION_CODENAME to $UBUNTU_CODENAME 
# if you're on an Ubuntu-based distro (eg, Linux Mint)
echo \
  "deb \
    [arch=$(dpkg --print-architecture) signed-by=/etc/apt/keyrings/docker.asc] \
    https://download.docker.com/linux/debian \
  $(. /etc/os-release && echo "$VERSION_CODENAME") stable" | \
  sudo tee /etc/apt/sources.list.d/docker.list > /dev/null
sudo apt-get update
sudo apt-get install docker-ce docker-ce-cli containerd.io docker-buildx-plugin docker-compose-plugin

# add current user to docker group so that one can run docker without sudo
sudo groupadd docker
sudo usermod -aG docker $USER


# for fedora
sudo dnf upgrade --refresh
sudo dnf install -y git clang cmake ninja clang-tools-extra valgrind

# copied from Docker docs
sudo dnf -y install dnf-plugins-core
sudo dnf config-manager --add-repo https://download.docker.com/linux/fedora/docker-ce.repo
sudo dnf install docker-ce docker-ce-cli containerd.io docker-buildx-plugin docker-compose-plugin
# If prompted to accept the GPG key, verify that the fingerprint matches 
# 060A 61C5 1B55 8A7F 742B 77AA C52F EB6B 621E 9F35, and if so, accept it.

# docker engine won't start by default, so:
sudo systemctl start docker

# add current user to docker group so that one can run docker without sudo
sudo groupadd docker
sudo usermod -aG docker $USER
```

- If you're on VS Code, set up as follow:
  - Install extensions:
    - C/C++ extension pack, which also includes CMake Tools.
    - Dev container. Optional.
    - markdownlint. Optional, but essential if writing documents.
    - Clang-Format.
    - YAML. Pretty much unnecessary, only to configure YAML files, such as the .clang-format file.
    - GitHub Actions. Optional, only useful to check how your GitHub actions go.
    - GitHub Pull Request. Optional, since, browser.
  - After that, click on the CMake icon on the left-hand-side bar.
  - In the "Configure" tab, choose the Clang kit.
  - The extension should know enough to figure out the rest.

- If you're on NeoVim or any other editors using clang-analyzer LSP, set up as follow:
  - Run the convenience script to generate a compile_commands.json:

  ```bash
  ./cmake-default-init.sh
  # create a symlink at the project root
  ln -s build/compile_commands.json compile_commands.json
  ```

  - After that, clang-analyzer should figure itself out.

### For Windows system

> [!NOTE]
> This part is mainly for building a Windows-native executable. If you just need to see the thing run, opt for the [dev container](#set-up-development-environment) way.
>

#### Way 1

- Set up WSL2 with your favorite Linux distro.
- Then, follow the [Unix system setup](#unix-systems).

#### Way 2

- This sets up your VS Code to build a Windows-native executable.
- There's a good chance this works on other IDEs also, but we mainly use VS Code.

> [!NOTE]
> Make sure to have VS Code and Git Bash installed (which, you should, already)
>
> [!NOTE]
> Note down the installation path if needed
>

- Download the following:
- git
- MSYS2 [following this link](https://www.mingw-w64.org/downloads/#msys2)
- Docker. Optional, only for running dev container.
- Then, do as follow:

1. After downloading MSYS2, find the UCRT64 executable and run
(located at <install_path>\ucrt64.exe, I believe?)
2. Inside the UCRT64 terminal, run:

  ```bash
  pacman -Syuu
  # assuming you're on x86_64
  # if you're on an ARM machine, change x86_64 to aarch64
  # compiler
  pacman -S git gcc clang ninja cmake \
  mingw-w64-x86_64-clang-tools-extra
  pacman -Syuu
  ```

- After that, you have enough tools to compile this project.
- Finally, add these tools to the environment variables:

1. Press `Window`, search for "environment variables".
2. Click on the first result, which leads to the list of environment variables.
3. Click "Add", and paste in <install_path>\ucrt64\bin.
4. Close the window.

- Now, fork this repository, then clone your fork, and do the setup:

1. Open terminal, make sure you're at the root directory of this project.
2. Run `code .`, which launches VS Code.
3. In VS Code, create a new directory called "build"
at the root directory of the project.
4. Open the integrated terminal and run the following to build an executable.
After that, run the executable:

```bash
./cmake-default-init.sh
cd build && cmake --build .
./smoldb.exe
```

> [!NOTE]
> As of writing this doc, nothing will happen when running the executable. But, it is to be expected.
> If nothing happens, then it ran without an error.
>