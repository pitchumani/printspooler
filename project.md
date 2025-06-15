# Print Spooler Project
Goal: Create a print spooler that manages print jobs and simulates printing.
## Overview
The print spooler will handle multiple print jobs, manage their states, and simulate the printing process. It will include features such as adding jobs, removing jobs, and displaying the status of each job.
## Features
- Add print jobs with details (job ID, document name, priority).
- Remove print jobs.
- Display the status of all print jobs.
- Simulate the printing process with a delay.
- Handle job priorities (higher priority jobs are printed first).
## Components
- **Job Class**: Represents a print job with attributes like job ID, document name, priority, and status.
- **PrintSpooler Class**: Manages a list of print jobs, handles adding, removing, and displaying jobs.
- **Main Function**: Provides a user interface to interact with the print spooler.
## Implementation Steps
1. Define the `Job` class with attributes for job ID, document name, priority, and status.
2. Define the `PrintSpooler` class with methods to add, remove, and display jobs.
3. Implement a method to simulate printing with a delay.
4. Create a main function to provide a command-line interface for users to interact with the print spooler.
5. Implement priority handling to ensure higher priority jobs are printed first.
6. Test the print spooler with various job scenarios to ensure it works as expected.
