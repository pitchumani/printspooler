# Print Spooler
The print spooler is a software simulation program that manages print jobs sent to a printer. It acts as a buffer between the computer and the printer, allowing multiple print jobs to be queued and printed in an orderly fashion. The spooler also provides features such as job prioritization, status monitoring, and error handling.

## Features
- Add print jobs with details (job ID, document name, priority).
- Remove print jobs.
- Display the status of all print jobs.
- Simulate the printing process with a delay.
- Handle job priorities (higher priority jobs are printed first).

## Usage
```bash
Usage: ./printspooler [options]
Options:
  --print <document>      Print the specified document
  --cancel <job_id>       Cancel the specified print job
  --status                Check the status of the print spooler
  --list <jobs|printers>  List all print jobs or printers
  --help                  Show this help message
  --add <printer>         Add the printer to the list
  --verbose               Enable verbose outputs
```
## Building and Running
TBD

## LICENSE
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.