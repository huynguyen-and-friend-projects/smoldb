# Set up development environment

<!--toc:start-->
- [Set up development environment](#set-up-development-environment)
  - [The lazy way](#the-lazy-way)
  - [The normal way](#the-normal-way)
    - [Unix systems](#unix-systems)
    - [For Windows system](#for-windows-system)
<!--toc:end-->

- There are 2 ways, the "lazy" way and the "normal" way.

## The lazy way
> [!IMPORTANT]
> Make sure you have Docker Engine and/or Docker Desktop installed
  > [follow the documentation](https://docs.docker.com/engine/install/)

- For more detail, follow [the documentation from Visual Studio Code themselves](https://code.visualstudio.com/docs/devcontainers/containers).
- This is applicable to Visual Studio Code ~~snobs~~ users, and works on any platform.

1. Install the Docker and Dev Container extensions.
2. Run the dev container. The Dockerfile used is [this one](../.devcontainer/dev.container.Dockerfile).
3. Wait for the image to build.
    - The Makefile extension may warn you about "dry run." Just keep running.
4. Enjoy your dev environment.
5. After getting into the container, run:
```bash
git config --local -e
```
- Then add the following
```ini
[user]
    name="YOUR NAME"
    email="YOUR EMAIL"
```

## The normal way
> [!IMPORTANT]
> I have yet to consider "official" support for Windows. Even some functionalities in the Makefile need Unix command-line
> 

### Unix systems
- Download the following:
    - git, obviously.
    - make
    - clang or gcc.
    - valgrind; optional, if on Linux
    - docker. [Follow the documentation](https://docs.docker.com/engine/install/)

> [!NOTE]
> If you use a Debian-based Linux distro (Debian itself, Ubuntu, Mint, ...), you can install build-essential, which includes
> gcc and make
>

- An example script for Debian-based distro
```bash
# for debian
sudo apt-get update
sudo apt-get install -y git build-essential valgrind

# copied from Docker documentation
sudo apt-get install ca-certificates curl
sudo install -m 0755 -d /etc/apt/keyrings
sudo curl -fsSL https://download.docker.com/linux/debian/gpg -o /etc/apt/keyrings/docker.asc
sudo chmod a+r /etc/apt/keyrings/docker.asc
# Add the repository to Apt sources:
# Replace $VERSION_CODENAME to $UBUNTU_CODENAME if you're on an Ubuntu-based distro (eg, Linux Mint)
echo \
  "deb [arch=$(dpkg --print-architecture) signed-by=/etc/apt/keyrings/docker.asc] https://download.docker.com/linux/debian \
  $(. /etc/os-release && echo "$VERSION_CODENAME") stable" | \
  sudo tee /etc/apt/sources.list.d/docker.list > /dev/null
sudo apt-get update
sudo apt-get install docker-ce docker-ce-cli containerd.io docker-buildx-plugin docker-compose-plugin

# add current user to docker group so that one can run docker without sudo
sudo groupadd docker
sudo usermod -aG docker $USER


# for fedora
sudo dnf upgrade --refresh
sudo dnf install -y git clang make valgrind

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

### For Windows system
> [!IMPORTANT]
> Due to limited resources, Windows support isn't currently considered. At best, run using WSL2
>

- Set up WSL2 with your favorite Linux distro.
- Then, follow one of the setups listed preceding.

## Building and testing
- If you have all the dependencies preceding downloaded, simply run:
```bash
make check
```
- Otherwise, use Docker:
1. Make sure you're at root directory of this project.
2. Run:
```bash
docker build -t smoldb-img .
docker compose -f test.compose.yml up
# or docker compose -f cli.compose.yml up to see the CLI in action
```
> [!NOTE]
> The two compose files expect the image `smoldb-img`.
>
3. After finishing, remove the containers:
