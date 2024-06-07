# Set up development environment

> [!IMPORTANT]
> This documentation focuses mainly on setting up VS Code.
> If you want to set up NeoVim, you can issue a documentation update.
>

<!--toc:start-->
- [Set up development environment](#set-up-development-environment)
  - [The lazy way](#the-lazy-way)
  - [The normal way](#the-normal-way)
    - [Unix systems](#unix-systems)
    - [For Windows system](#for-windows-system)
      - [Way 1](#way-1)
      - [Way 2](#way-2)
    - [How-to](#how-to)
<!--toc:end-->

- There are 2 ways, the "lazy" way and the "normal" way.

## The lazy way

> [!IMPORTANT]
> Make sure you have Docker Engine and/or Docker Desktop installed
> [follow the documentation](https://docs.docker.com/engine/install/)

- For more detail, follow [the documentation from Visual Studio Code themselves](https://code.visualstudio.com/docs/devcontainers/containers).
- This is applicable to Visual Studio Code ~~snobs~~ users, and works on any platform.

> [!NOTE]
> If you're on Windows/Mac, this is also the easiest way to use valgrind
>

1. Install the Docker and Dev Container extensions.
2. Run the dev container. The Dockerfile used is [this one](../.devcontainer/Dockerfile).
3. Wait for the image to build.
 The image also configures CMake to
 setup build system for a Linux debug version using clang.

> [!IMPORTANT]
> When you exit the dev container, be sure to re-configure CMake build
> with the convenience script. If you're on Windows, use git bash
>
> ```bash
> sudo rm -rf ./build
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
  - vale; optional, if you're planning to edit documentation
  - docker. [Follow the documentation](https://docs.docker.com/engine/install/)

> [!NOTE]
> If you're on Mac, consider installing Brew to more easily download the packages.
>

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

- Then fork and clone the project and run:

```bash
cd smoldb
code .
```

- Which opens VS Code at that directory.
- If you're on VS Code, set up as follow:
  - Install extensions:
    - C/C++ extension pack, which also includes CMake Tools.
    - Dev container. Optional.
    - markdownlint. Optional, but essential if writing documents.
    - Clang-Format.
    - Vale VSCode. Optional, but essential if writing documents.
    - YAML. Pretty much unnecessary,
    only to configure YAML files, such as the .clang-format file.
    - GitHub Actions. Optional, only useful to check how your GitHub actions go.
    - GitHub Pull Request. Optional, since, browser.
  - After that, click the CMake icon on the left-hand-side bar.
  This open the CMake extension menu.
  - In the "Configure" tab, choose the Clang kit.
  - In the "Debug" tab, choose either smoldb or smoldb install.
    - If you choose smoldb install, remember to run this after every build

    ```bash
    cmake --install build
    ```

- If you're on NeoVim or any other editors using clang-analyzer, set up as follow:
  - Run the convenience script to generate a compile_commands.json:

  ```bash
  sudo rm -rf ./build
  ./cmake-default-init.sh
  # create a symlink at the project root
  ln -s build/compile_commands.json compile_commands.json
  # build and install
  cmake --build build && cmake --install build
  ```

  - After that, clang-analyzer should figure itself out.
  - To debug the project, make sure you have nvim dap installed.
  Preferably, configure C/C++ to use lldb-vscode.
  - You should debug using the executable.

### For Windows system

> [!NOTE]
> This part is mainly for building a Windows-native executable.
> If you just need to see the thing run,
> opt for the [dev container](#the-lazy-way) way.
>

#### Way 1

- Set up WSL2 with your favorite Linux distro.
- Then, follow the [Unix system setup](#unix-systems).

#### Way 2

- This sets up your VS Code to build a Windows-native executable.
- There's a good chance this works on other IDEs also, but mainly VS Code.

> [!NOTE]
> Make sure to have VS Code and Git Bash installed,
> and also note down installation path if needed.

- Download the following:
- git
- MSYS2 [following this link](https://www.mingw-w64.org/downloads/#msys2)
- Docker. Optional, only for running dev container.
- choco. Optional, to download Vale, necessary for editing documentation.
  - To install choco, [follow this documentation](https://chocolatey.org/install#individual)
  - To install Vale with choco, open Command Prompt as Administrator and run:

  ```pwsh
  choco install vale
  ```

- Then, do as follow:

1. After downloading MSYS2, find the UCRT64 executable and run it.
2. Inside the UCRT64 terminal, run:

  ```bash
  pacman -Syuu
  # assuming you're on x86_64
  # if you're on an ARM machine, change x86_64 to aarch64
  # compiler
  pacman -S mingw-w64-ucrt-x86_64-clang \
  mingw-w64-ucrt-x86_64-ninja mingw-w64-ucrt-x86_64-cmake \
  mingw-w64-ucrt-x86_64-clang-tools-extra
  pacman -Syuu
  ```

- After that, you have enough tools to compile this project.
- Finally, add these tools to the environment variables:

1. Press `Window`, search for "environment variables."
2. Click on the first result, which leads to the list of environment variables.
3. Click "Add," and paste in <install_path>\ucrt64\bin.
4. Close the window and terminal. After that, open Command Prompt.
5. In Command Prompt, check if it can recognize the packages:

```bash
clang --version
ninja --version
cmake --version
clang-format --version
clang-tidy --version
```

- If you're on VS Code, set up as follow:
  - Install extensions:
    - C/C++ extension pack, which also includes CMake Tools.
    - Dev container. Optional.
    - markdownlint. Optional, but essential if writing documents.
    - Clang-Format.
    - Vale VSCode. Optional, but essential if writing documents.
    - YAML. Pretty much unnecessary,
    only to configure YAML files, such as the .clang-format file.
    - GitHub Actions. Optional, only useful to check how your GitHub actions go.
    - GitHub Pull Request. Optional, since, browser.

- Now, fork this repository, then clone your fork, and do the setup:

1. Open terminal, make sure you're at the root directory of this project.
2. Run `code .`, which launches VS Code.
3. In VS Code, find the CMake extension icon. Click on it.
A config menu is then opened.
4. Inside CMake configuration menu, click "select kit," and choose the Clang kit.
It should configure everything for you.
5. Next, at the Debug section, choose any of them.
6. Down at the Project Outline menu, click Build on the smoldb executable.
7. Check that there is an executable inside the directory build.
8. Run the following command after every rebuild to pull the executable to
the project root, then run it:

```pwsh
cmake --install build
.\smoldb.exe
```

> [!NOTE]
> As of writing this doc, nothing happens when running the executable.
> But, nothing unexpected.
> If nothing happens, then it ran without an error.
>

## How-to

- Build and run the executable
  - Make sure you have followed the steps preceding.
  - If you use VS Code, simply navigate to the CMake config menu,
  and click Build on the smoldb executable.
  - To build with command-line instead, run the following at the project root:

  ```bash
  cmake --build build
  cmake --install build
  ```

- Debug
  - First, build the executable in debug mode.
  - If you're on VS Code, open the Command Palette with `Ctrl+Shift+P`,
  find "CMake: Debug" and run.
  - If you use NeoVim, use nvim-dap to debug.
  - Or, if you're a gigachad and like gdb/lldb in the terminal, do it your way.
  I have yet to reach that realm.

- Format and lint your code
  - You can use the convenience script:

  ```bash
  ./clang-format-lint-all.sh
  ```

  - In VS Code, you can also do as follow:
    - Open Settings, find "format on save" and turn it on.
    Then, every time you save, clang-format does its work.
    - Then, find "code analysis," and tick the checkbox of
    C/Cpp > Code analysis > Clang Tidy: Enabled and
    C/Cpp > Code analysis: Run automatically
  - This could throw you quite a lot of coding-style errors, as expected.

- Format and lint the Markdown documentation
  - Make sure to make markdownlint and vale installed.
    - On VS Code, download the markdownlint and vale extensions,
    then download the vale command-line tool.
    - If you haven't, created a directory at your user root called `vale`,
    and inside that, create a file called .vale.ini.
    - Add the following to .vale.ini:

    ```yaml
    StylePath: .
    Packages: Google
    ```

    - Save, open the command line, run the following to download the package:

    ```bash
    vale sync
    ```
