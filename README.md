# Process Management Exercise in Linux

This exercise demonstrates the effect of using `kill`, `kill -15` (SIGTERM), and `kill -9` (SIGKILL) on a parent and child process relationship in Linux.

## Prerequisites
Ensure you have access to a Linux system with the following tools installed:
- `gcc` (GNU Compiler Collection)
- `git` (for cloning the repository)

## Step 1: Install Required Packages
Before compiling the program, install `gcc` if it is not already installed:

```sh
sudo dnf install -y gcc git
```

## Step 2: Clone the Repository
Clone the GitHub repository containing the `myapp.c` file:

```sh
git clone https://github.com/stv707/linux_process.git
cd linux_process
```

## Step 3: Compile the Program
Use `gcc` to compile the program:

```sh
gcc -o myapp myapp.c
```

This will create an executable file named `myapp`.

## Step 4: Run the Program
Execute the compiled program:

```sh
./myapp
```

The program will:
- Spawn three child processes.
- Continue running until manually terminated.

## Step 5: Find the Parent and Child Process IDs
Open another terminal and find the process IDs:

```sh
ps aux | grep myapp
```

You should see multiple processes running, with one parent process and three child processes.

## Step 6: Experiment with Different Kill Signals
### Kill a Child Process
Pick a child PID and terminate it:

```sh
kill <child_pid>
```

You should see that the parent process detects the termination and respawns the child.

### Kill the Parent Process Using SIGTERM (`kill -15`)
Terminate the parent process gracefully:

```sh
kill -15 <parent_pid>
```

Expected Behavior:
- The parent process will terminate.
- It will also terminate all child processes before exiting.

### Kill the Parent Process Using SIGKILL (`kill -9`)
Forcefully terminate the parent process:

```sh
kill -9 <parent_pid>
```

Expected Behavior:
- The parent process will be immediately killed.
- The child processes will continue running and become orphaned.
- They will eventually be adopted by the `init` (PID 1) process.

## Step 7: Verify Orphaned Processes
After killing the parent with `kill -9`, check the child processes:

```sh
ps aux | grep myapp
```

You will see that the child processes are still running, now adopted by `init`.

## Step 8: Clean Up
To manually kill all remaining processes:

```sh
pkill myapp
```

This will ensure that no processes remain running.

## Summary
- **`kill <pid>`**: Terminates a child process, parent respawns it.
- **`kill -15 <pid>`**: Gracefully terminates the parent, also killing children.
- **`kill -9 <pid>`**: Immediately kills the parent, leaving child processes orphaned.

This exercise helps understand how process management works in Linux and why `kill -9` should be used with caution.

---

**End of Exercise**

