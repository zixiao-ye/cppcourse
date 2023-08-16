**CIIP C++ Course**

Welcome to the CIIP course **Concepts of C++ programming**!

You will use this [git](https://git-scm.org) repository for solving and submitting homeworks.

**Table of Contents**

[[_TOC_]]


# Overview


You will have to work with multiple git repos:
- `upstream` remote: new assignments provided by us on GitLab
- `origin` remote: your code submissions on GitLab
- the local repo on your computer: where you create and commit your work.

`origin` is your personal "fork" of the [base repo](https://gitlab.lrz.de/cppcourse/ws2022/tasks).
`origin` is used for your grading, and it's stored on GitLab as (`your-username_tasks`).

You will [pull](https://git-scm.com/docs/git-pull) new assignments from our base repo (`upstream`) and [push](https://git-scm.com/docs/git-push) your changes to your personal repo (`origin`) to submit your solutions.
That way, you "download" our new assignment from the base repo to your computer and then "upload" your solution to your GitLab repo for grading.

**Getting and Submitting new Homeworks**
We will publish new homeworks (and bugfixes :) [**in the base repo**](https://gitlab.lrz.de/cppcourse/ws2022/tasks), which you then merge into [**your repo**](https://gitlab.lrz.de/cppcourse/ws2022) (`your-username_tasks`).
If everything is setup correctly it is as simple as (*pseudo code!*):

``` console
$ git pull upstream master        # get the new homework assignment from us
# ~~ do the homework ~~
$ git status                      # see how git thinks about your files
$ git add ....                    # add the changes you want to commit
$ git commit -m "my submission"   # create the commit
$ git push origin master          # upload the changes to your GitLab repository
```
Pushing the changes will trigger our automatic build server, which compiles your code and runs the unit tests ([CI](https://en.wikipedia.org/wiki/Continuous_integration#Workflows)).
At the end of each assignment period, we will collect your submission, verify your solution and then notify you in an [issue](https://docs.gitlab.com/ee/user/project/issues/) if your submission passed or not.


# Setup

This section explains how you set everything up on your machine.
If you have any questions, post it on [Zulip](https://zulip.in.tum.de/) so that we can help you and other students can refer to it.


## SSH-Key

Instead of always typing your username and password when communicating with GitLab using git, we recommend to set up an SSH key.

1. [Generate an SSH key pair](https://docs.gitlab.com/ee/user/ssh.html#generate-an-ssh-key-pair)
2. [Add an SSH key to your GitLab account](https://docs.gitlab.com/ee/user/ssh.html#add-an-ssh-key-to-your-gitlab-account)
3. Add the new key to you computer's `ssh` config:
   In your home folder (`~/` on Mac/Linux and `C:\Users\You` on Windows) you should now see the `.ssh` (hidden) folder, containing the new SSH-Key (provided you saved the file in the default directory).
   To instruct SSH to use a specific key file with LRZ GitLab, you can create a new file in that directory named `.ssh/config` (without any file suffix) and add this content:

```
Host gitlab.lrz.de
  Preferredauthentications publickey
  IdentityFile ~/.ssh/#your-private-key-file#
```


## Git

You'll need `git` in order to interact with your repository. [This tutorial](https://git-scm.com/book/en/v2/Getting-Started-Installing-Git),
will show you the installation process for most operating systems.


## Downloading your Repository (Clone)

- On GitLab you get your remote link by clicking on `Clone` on the main page of your repository.
- Choose the link under *Clone with SSH*.
- Navigate to the directory where you want to download your project and use `git clone <your-link>`, i.e
use:
  - `git clone git@gitlab.lrz.de:cppcourse/ws2022/your-username_tasks.git`
  - alternative: `git clone https://gitlab.lrz.de/cppcourse/ws2022/your-username_tasks.git` if you don't want to use `ssh`, but `https` instead


## Adding Upstream


In order to regularly pull the new assignments and any other changes (bugfixes), you must add the original [base repo](https://gitlab.lrz.de/cppcourse/ws2022/tasks) as `upstream` remote.

To do this, navigate to your cloned project's directory and use the following commands from the console:

First check the original setup with:
```console
$ git remote -v
```

The output should be:
```console
> origin  git@gitlab.lrz.de:cppcourse/ws2022/your-username_tasks.git (fetch)
> origin  git@gitlab.lrz.de:cppcourse/ws2022/your-username_tasks.git (push)
```
which tells us, that your local git repo knows a remote git repo with the name `origin`, which is your personal GitLab repo.

Now you need to add "[the course organizer's](https://gitlab.lrz.de/cppcourse/ws2022/tasks)" repo so you can get new tasks from us.
To register it as a new remote repo, run:
```console
$ git remote add upstream git@gitlab.lrz.de:cppcourse/ws2022/tasks.git
```
Now you've added our git base repo as `upstream`.
Again, you can verify that it was added:
```console
$ git remote -v
> origin  git@gitlab.lrz.de:cppcourse/ws2022/your-username_tasks.git (fetch)
> origin  git@gitlab.lrz.de:cppcourse/ws2022/your-username_tasks.git (push)
> upstream  git@gitlab.lrz.de:cppcourse/ws2022/tasks.git (fetch)
> upstream  git@gitlab.lrz.de:cppcourse/ws2022/tasks.git (push)
```
With this configuration, your local `git` repo can now talk to two independent remote `git` repositories:
* `origin` is your repo on GitLab, where you commit your homework results
* `upstream` is our repo on GitLab, where we publish new assignments

So you're now dealing with **3 repos**: Your local repo, your submission remote repo, and the new-tasks remote repo.



## Getting new Assignments


If you want to get the new assignments or other changes, go to your project directory and use:
```console
$ git pull upstream master    # download and merge our changes to your local repo
```

This first connects to our server and downloads the information from the base project, where we publish the homeworks to.
Then, it merges our `upstream/master` contents into your local `master` branch.
For new assignments, we always use new files, so this should work without any merge conflicts.

However, if both of us changed the same file, a merge conflict might happen if the changes aren't compatible, in which case you need to resolve the conflict before you can start working.


## Operating System

We're cannot stress enough that your lecture experience using Windows will most likely be painful.
You should really consider installing Linux (e.g. [Ubuntu](https://ubuntu.com)) (also possible alongside Windows), or at least use Linux on Windows (the [WSL](https://learn.microsoft.com/en-us/windows/wsl/)).


## Compiler

As we'll be covering modern C++ (C++20) you need a recent compiler, otherwhise your project will not compile.

Recommended compilers are:
- GNU GCC 11 and higher (Linux: install `g++` with your package manager, [Windows](https://nuwen.net/mingw.html))
- LLVM Clang 13 and higher
- (Visual Studio 2022 17.0 and higher)

We will be testing with GCC 11 and Clang 13 on Linux.
It therefore could be possible that you encounter errors with other versions.


## Build system (CMake)

For later assignments we use the [CMake](https://cmake.org/) build system.
It takes care of building/compiling everything in the right order and hooking everything up, rather than forcing us to manually manage (and possibly forget) some elements or links.
Follow [this tutorial](https://cmake.org/install/) to install CMake.


## IDE

You can use any text editor you are comfortable with.
We use [Doom](https://github.com/doomemacs/doomemacs) [Emacs](https://www.gnu.org/software/emacs/), [Spacemacs](https://www.spacemacs.org/) (both unify the advantages of Vim and Emacs) and [vim](https://www.vim.org/)/[neovim](https://neovim.io/).
If you don't have any preference yet, we recommend [CLion](https://www.jetbrains.com/community/education/#students) or [VSCode](https://code.visualstudio.com/).


# Troubleshooting



## Unexpected Contents


To ensure the tests are unmodified for grading, we check if the file content hashes are correct.

During the CI run, we validate that `/CMakeLists.txt` and the `tests/` directory are as expected, but we can't pre-check `/.gitlab-ci.yml` without breaking the universe.

Do not modify these files - otherwise your homework can't be graded!

If you do modify them and get an error message, you must not fix your code by rewriting git repo history (using `git force-push`) - you can only ever add new things to your repo history, not delete old history elements.


### Fixing Unexpected Contents


You can always make sure the files are in the "correct" state by running:

```bash
# if you want, inspect what you've changed
git diff upstream/master..HEAD CMakeLists.txt tests/ .gitlab-ci.yml

# undo the changes
git restore -s upstream/master CMakeLists.txt tests/ .gitlab-ci.yml

# and commit what is needed to undo your changes
git add CMakeLists.txt tests/ .gitlab-ci.yml
git commit -m "restore important files i should not have modified"
```
