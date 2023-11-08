<h1 align="center"><img src="https://user-images.githubusercontent.com/62793491/208452652-71416c5c-8261-4501-a002-afc9e2cf0a0b.png" width="224px"/><br/>
  Livl OS
</h1>  
<p align="center">Livl OS contains all the different labs exercice from Systems class</p>  

# Table of Contents
- [📦 Prerequisites](#-prerequisites)
- [🚀 Quick start](#-quick-start)
- [📁 Project structure](#-project-structure)
- [🔧 Pipeline](#-pipeline)
- [🧍🏽Project team](#-project-team)

# **📦 Prerequisites**
This project is developed in C language, so you need to have a C compiler installed on your machine. It would be better to run it on a Linux distribution, but it is possible to run it on Windows with the WSL (Windows Subsystem for Linux).

- `gcc` : `sudo apt install gcc`
- `make`: `sudo apt install make`

> To install the WSL, follow this [tutorial](https://docs.microsoft.com/en-us/windows/wsl/install-win10).

# 🚀 Quick start
- In the root folder, go to the lab folder you want to use (ex: `cd 02-proc`)
- Run `make` to compile the project
- Run `./bin/<file>` to run the executable file generated by the `make` command
- Run `make clean` to clean the project


# **📁 Project structure**

- Each lab is in a folder named `<lab-number>-<exercise-name>`
- Each lab folder contains the following structure:

```
<lab-number>-<exercise-name>
├── bin/
│   └── file
├── include/
│   └── file.h
├── src/
│   └── file.c
└── Makefile
```

# **🔧 Pipeline**

- The pipeline is configured to run on each push and pull request on the `master` branch
- The pipeline is iterating over each directory in the root folder and run the `make` command if a `Makefile` is present
- The pipeline is also running the `make clean` command to clean the project after the `make` command

> You can find the pipeline configuration in the [`.github/workflows/c-make.yml`](.github/workflows/c-make.yml) file.

# **🧍🏽Project team**

<table align="center">
    <tr>
        <th><img src="https://avatars.githubusercontent.com/u/19238963?v=4?v=4?size=115" width="115"><br><strong>@FranckG28</strong></th>
        <th><img src="https://avatars.githubusercontent.com/u/62793491?v=4?size=115" width="115"><br><strong>@jvondermarck</strong></th>
    </tr>
    <tr align="center">
        <td><b>Franck Gutmann</b></td>
        <td><b>Julien Von Der Marck</b></td>
    </tr>
</table>