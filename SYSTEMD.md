# Daemonizing `myapp` using systemd

This guide will walk you through setting up `myapp` as a systemd service, ensuring it runs in the background as a daemon.

## Step 1: Move the Compiled Binary
First, ensure that the compiled `myapp` binary is placed in `/usr/local/bin` for system-wide availability:

```sh
sudo mv myapp /usr/local/bin/
```

## Step 1a 
### SELinux prevention - Due to SELinux, the process may not run
```sh 
chcon -t bin_t /usr/local/bin/myapp

sudo restorecon -v /usr/local/bin/myapp
sudo restorecon -Rv /usr/local/bin

```


## Step 2: Create a systemd Unit File
Create a new systemd service unit file in `/etc/systemd/system/`:

```sh
sudo vim /etc/systemd/system/myapp.service
```

Add the following content to define the service:

```ini
[Unit]
Description=MyApp Daemon Process Management Demo
After=network.target

[Service]
ExecStart=/usr/local/bin/myapp
Restart=always
User=root
Group=root
StandardOutput=syslog
StandardError=syslog
SyslogIdentifier=myapp

[Install]
WantedBy=multi-user.target
```

Save the file and exit the editor.

## Step 3: Reload systemd to Recognize the New Service
Execute the following command to reload systemd and recognize the new unit file:

```sh
sudo systemctl daemon-reload
```

## Step 4: Enable the Service on Boot
Enable the service so it starts automatically at boot:

```sh
sudo systemctl enable myapp
```

## Step 5: Start the Service
Start `myapp` as a daemon:

```sh
sudo systemctl start myapp
```

## Step 6: Verify the Service Status
Check if the service is running correctly:

```sh
sudo systemctl status myapp
```

You should see output indicating that `myapp` is running as a background service.

## Step 7: Managing the Service
- **To stop the service:**
  ```sh
  sudo systemctl stop myapp
  ```
- **To restart the service:**
  ```sh
  sudo systemctl restart myapp
  ```
- **To check logs:**
  ```sh
  journalctl -u myapp --no-pager | tail -n 20
  ```

## Step 8: Disable the Service (Optional)
If you no longer want `myapp` to start on boot:

```sh
sudo systemctl disable myapp
```

## Step 9: Remove the Service (Optional)
If you want to remove `myapp` from systemd:

```sh
sudo systemctl stop myapp
sudo systemctl disable myapp
sudo rm /etc/systemd/system/myapp.service
sudo systemctl daemon-reload
```

## Summary
- We moved the compiled binary to `/usr/local/bin`.
- Created a systemd unit file to daemonize `myapp`.
- Enabled and started the service using `systemctl`.
- Learned how to manage and remove the service.

This setup ensures that `myapp` runs as a background daemon and restarts automatically if it crashes.

---

**End of Guide**

