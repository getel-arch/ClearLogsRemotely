# ClearLogsRemotely
 
## Build
```
gcc .\src\clear_log_remotely.c -o clear_log_remotely.exe -s -m64 -lwevtapi
```

## Usage
```
clear_log_remotely.exe 192.168.88.60 Microsoft-Windows-TaskScheduler/Operational
```