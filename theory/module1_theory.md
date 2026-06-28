# Module 1 Theory & Conceptual Questions

## Q9. Explain the difference between `git pull`, `git fetch`, and `git clone`. When would you use each?

These three commands represent the core mechanisms Git uses to interact with remote repositories, but they operate at entirely different stages of the development workflow:

### 1. `git clone`
* **What it does:** Copies an existing remote repository down from the cloud and initializes a brand-new local repository on your machine. It downloads all files, branches, directories, and the entire commit history.
* **When to use it:** Use this **only once** at the beginning of a project when you want to set up a local workspace for a repository that already exists on GitHub (e.g., when downloading a partner's repository or starting work on a new machine).

### 2. `git fetch`
* **What it does:** Downloads the latest metadata, commits, and branch changes from the remote repository (GitHub) into your local repository *without* altering your local working files. It simply updates your local tracking branches (like `origin/main`).
* **When to use it:** Use this when you want to safely see what your team members have pushed online without letting their changes overwrite or mess with the code you are actively writing.

### 3. `git pull`
* **What it does:** Executes a two-step process: it runs `git fetch` to download the latest changes from GitHub, and then immediately runs `git merge` to fuse those remote changes into your active local branch.
* **When to use it:** Use this when you start your workday or before making a new feature branch to ensure your local workspace is completely synchronized with the newest version of the project online.

---

## Q10. What is a `.gitignore` file? Write a `.gitignore` for an Arduino project that excludes compiled output files, OS-specific files, and IDE config folders.

A `.gitignore` file is a plain text configuration file placed at the root of a Git repository. It tells Git explicitly which files or folders to ignore, track over, or completely skip when staging changes (`git add`). 

In embedded systems development, it is highly critical because compiling firmware creates temporary binary files that are hardware-specific and do not belong in version control.

### Standard Production-Grade `.gitignore` for Arduino Projects:

```ini
# =========================================================================
# Compiled Firmware & Build Artifacts (Excludes compiled output files)
# =========================================================================
*.hex
*.elf
*.o
*.d
build/
bin/

# =========================================================================
# IDE and Local Editor Configurations (Excludes config folders)
# =========================================================================
.vscode/
.idea/
*.swp
*.bak
.cmake/

# =========================================================================
# OS-Specific System Logs (Excludes OS-specific files)
# =========================================================================
.DS_Store
Thumbs.db
ehthumbs.db
Desktop.ini

# =========================================================================
# Security & Secret Configurations (Prevents pushing private keys/passwords)
# =========================================================================
config.h
secrets.h
.env