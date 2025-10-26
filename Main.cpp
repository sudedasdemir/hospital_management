#include <iostream>
#include <vector>
#include <string>
#include <limits> // Required for numeric_limits
#include <memory>    // For std::shared_ptr

#include "HospitalSystem.h" // Include the combined header file

// --- Helper Functions for User Input ---

// Function to get a non-empty string input from the user
std::string getValidatedStringInput(const std::string& prompt) {
    std::string input;
    do {
        std::cout << prompt;
        // Clears the input buffer to prevent issues with std::getline after std::cin >> int
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, input);
        if (input.empty()) {
            std::cout << "Input cannot be empty. Please try again." << std::endl;
        }
    } while (input.empty());
    return input;
}

// Function to get a validated integer input from the user
int getValidatedIntegerInput(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        if (std::cin.fail()) { // Check if input failed (e.g., non-numeric input)
            std::cout << "Invalid input. Please enter a number." << std::endl;
            std::cin.clear(); // Clear error flags
            // Discard invalid input from the buffer
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            // Clears the rest of the line from the buffer after a valid integer is read
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
    }
}

// Function to get a validated positive integer input from the user
int getValidatedPositiveIntegerInput(const std::string& prompt) {
    int value;
    while (true) {
        value = getValidatedIntegerInput(prompt); // Calls the general integer input function
        if (value > 0) {
            return value;
        } else {
            std::cout << "Value must be positive. Please try again." << std::endl;
        }
    }
}

// --- Main Program Logic ---

// Displays the main menu options
void displayMainMenu() {
    std::cout << "\n--- Hospital Management System Menu ---" << std::endl;
    std::cout << "1. Patient Management" << std::endl;
    std::cout << "2. Doctor Management" << std::endl;
    std::cout << "3. Appointment Management" << std::endl;
    std::cout << "4. Display All Patients" << std::endl;
    std::cout << "5. Display All Doctors" << std::endl;
    std::cout << "6. Display All Appointments" << std::endl;
    std::cout << "7. Exit" << std::endl;
    std::cout << "---------------------------------------" << std::endl;
}

// Displays the patient management sub-menu
void displayPatientMenu() {
    std::cout << "\n--- Patient Management ---" << std::endl;
    std::cout << "1. Add New Patient" << std::endl;
    std::cout << "2. Search Patient by ID" << std::endl;
    std::cout << "3. Search Patient by Name" << std::endl;
    std::cout << "4. Display Patient Medical History" << std::endl;
    std::cout << "5. Back to Main Menu" << std::endl;
    std::cout << "--------------------------" << std::endl;
}

// Displays the doctor management sub-menu
void displayDoctorMenu() {
    std::cout << "\n--- Doctor Management ---" << std::endl;
    std::cout << "1. Add New Doctor" << std::endl;
    std::cout << "2. Search Doctor by ID" << std::endl;
    std::cout << "3. Search Doctor by Name" << std::endl;
    std::cout << "4. Back to Main Menu" << std::endl;
    std::cout << "-------------------------" << std::endl;
}

// Displays the appointment management sub-menu
void displayAppointmentMenu() {
    std::cout << "\n--- Appointment Management ---" << std::endl;
    std::cout << "1. Book New Appointment" << std::endl;
    std::cout << "2. Reschedule Appointment" << std::endl;
    std::cout << "3. Back to Main Menu" << std::endl;
    std::cout << "------------------------------" << std::endl;
}

int main() {
    Hospital myHospital; // Create an instance of the Hospital system
    int choice;
    int subChoice;

    std::cout << "Welcome to the Hospital Management System!" << std::endl;

    do {
        displayMainMenu(); // Show main menu
        choice = getValidatedIntegerInput("Enter your choice: "); // Get user's main menu choice

        switch (choice) {
            case 1: // Patient Management
                do {
                    displayPatientMenu(); // Show patient sub-menu
                    subChoice = getValidatedIntegerInput("Enter your choice: ");
                    switch (subChoice) {
                        case 1: { // Add New Patient
                            std::string name = getValidatedStringInput("Enter patient name: ");
                            int age = getValidatedIntegerInput("Enter patient age: ");
                            std::string gender = getValidatedStringInput("Enter patient gender (Male/Female/Unknown): ");
                            std::string disease = getValidatedStringInput("Enter patient disease (N/A if none): ");
                            try {
                                // Create a new Patient object using shared_ptr for automatic memory management
                                std::shared_ptr<Patient> newPatient = std::make_shared<Patient>(name, age, gender, disease);
                                myHospital.addPatient(newPatient); // Add patient to hospital system
                                std::cout << "Patient " << name << " added successfully with ID: " << newPatient->getPatientID() << std::endl;
                            } catch (const std::invalid_argument& e) {
                                std::cerr << "Error adding patient: " << e.what() << std::endl;
                            }
                            break;
                        }
                        case 2: { // Search Patient by ID
                            int id = getValidatedPositiveIntegerInput("Enter patient ID to search: ");
                            std::shared_ptr<Patient> foundPatient = myHospital.searchPatient(id);
                            if (foundPatient) {
                                std::cout << "Patient found: ";
                                foundPatient->displayInfo();
                            } else {
                                std::cout << "Patient with ID " << id << " not found." << std::endl;
                            }
                            break;
                        }
                        case 3: { // Search Patient by Name
                            std::string name = getValidatedStringInput("Enter patient name to search: ");
                            bool caseSensitive = (getValidatedIntegerInput("Case-sensitive search? (1 for Yes, 0 for No): ") == 1);
                            std::shared_ptr<Patient> foundPatient = myHospital.searchPatient(name, caseSensitive);
                            if (foundPatient) {
                                std::cout << "Patient found: ";
                                foundPatient->displayInfo();
                            } else {
                                std::cout << "Patient with name '" << name << "' not found." << std::endl;
                            }
                            break;
                        }
                        case 4: { // Display Patient Medical History
                            int id = getValidatedPositiveIntegerInput("Enter patient ID to display medical history: ");
                            std::shared_ptr<Patient> foundPatient = myHospital.searchPatient(id);
                            if (foundPatient) {
                                foundPatient->displayMedicalHistory();
                            } else {
                                std::cout << "Patient with ID " << id << " not found." << std::endl;
                            }
                            break;
                        }
                        case 5: // Back to Main Menu
                            break;
                        default:
                            std::cout << "Invalid choice. Please try again." << std::endl;
                            break;
                    }
                } while (subChoice != 5);
                break;

            case 2: // Doctor Management
                do {
                    displayDoctorMenu(); // Show doctor sub-menu
                    subChoice = getValidatedIntegerInput("Enter your choice: ");
                    switch (subChoice) {
                        case 1: { // Add New Doctor
                            std::string name = getValidatedStringInput("Enter doctor name: ");
                            int age = getValidatedIntegerInput("Enter doctor age: ");
                            std::string gender = getValidatedStringInput("Enter doctor gender (Male/Female/Unknown): ");
                            std::string specialization = getValidatedStringInput("Enter doctor specialization: ");
                            int license = getValidatedIntegerInput("Enter doctor license number (0 if none): ");
                            try {
                                // Create a new Doctor object using shared_ptr
                                std::shared_ptr<Doctor> newDoctor = std::make_shared<Doctor>(name, age, gender, specialization, license);
                                myHospital.addDoctor(newDoctor); // Add doctor to hospital system
                                std::cout << "Doctor " << name << " added successfully with ID: " << newDoctor->getDoctorID() << std::endl;
                            } catch (const std::invalid_argument& e) {
                                std::cerr << "Error adding doctor: " << e.what() << std::endl;
                            }
                            break;
                        }
                        case 2: { // Search Doctor by ID
                            int id = getValidatedPositiveIntegerInput("Enter doctor ID to search: ");
                            std::shared_ptr<Doctor> foundDoctor = myHospital.searchDoctor(id);
                            if (foundDoctor) {
                                std::cout << "Doctor found: ";
                                foundDoctor->displayInfo();
                            } else {
                                std::cout << "Doctor with ID " << id << " not found." << std::endl;
                            }
                            break;
                        }
                        case 3: { // Search Doctor by Name
                            std::string name = getValidatedStringInput("Enter doctor name to search: ");
                            bool caseSensitive = (getValidatedIntegerInput("Case-sensitive search? (1 for Yes, 0 for No): ") == 1);
                            std::shared_ptr<Doctor> foundDoctor = myHospital.searchDoctor(name, caseSensitive);
                            if (foundDoctor) {
                                std::cout << "Doctor found: ";
                                foundDoctor->displayInfo();
                            } else {
                                std::cout << "Doctor with name '" << name << "' not found." << std::endl;
                            }
                            break;
                        }
                        case 4: // Back to Main Menu
                            break;
                        default:
                            std::cout << "Invalid choice. Please try again." << std::endl;
                            break;
                    }
                } while (subChoice != 4);
                break;

            case 3: // Appointment Management
                do {
                    displayAppointmentMenu(); // Show appointment sub-menu
                    subChoice = getValidatedIntegerInput("Enter your choice: ");
                    switch (subChoice) {
                        case 1: { // Book New Appointment
                            int patientId = getValidatedPositiveIntegerInput("Enter patient ID for appointment: ");
                            std::shared_ptr<Patient> patient = myHospital.searchPatient(patientId);

                            if (!patient) { // Check if patient was found
                                std::cout << "Patient with ID " << patientId << " not found. Cannot book appointment." << std::endl;
                                break;
                            }

                            int doctorId = getValidatedPositiveIntegerInput("Enter doctor ID for appointment: ");
                            std::shared_ptr<Doctor> doctor = myHospital.searchDoctor(doctorId);

                            if (!doctor) { // Check if doctor was found
                                std::cout << "Doctor with ID " << doctorId << " not found. Cannot book appointment." << std::endl;
                                break;
                            }

                            std::string date = getValidatedStringInput("Enter appointment date (YYYY-MM-DD): ");
                            std::string time = getValidatedStringInput("Enter appointment time (HH:MM AM/PM): ");

                            try {
                                // Create a new Appointment object using shared_ptr
                                std::shared_ptr<Appointment> newAppointment = std::make_shared<Appointment>(0, date, time, patient, doctor);
                                myHospital.addAppointment(newAppointment); // Add appointment to hospital system
                                std::cout << "Appointment booked successfully with ID: " << newAppointment->getAppointmentID() << std::endl;
                            } catch (const std::invalid_argument& e) {
                                std::cerr << "Error booking appointment: " << e.what() << std::endl;
                            }
                            break;
                        }
                        case 2: { // Reschedule Appointment
                            int appId = getValidatedPositiveIntegerInput("Enter appointment ID to reschedule: ");
                            std::shared_ptr<Appointment> foundApp = myHospital.searchAppointment(appId);

                            if (foundApp) {
                                std::cout << "Appointment found: ";
                                foundApp->displayInfo();
                                
                                std::string newDate = getValidatedStringInput("Enter new appointment date (YYYY-MM-DD): ");
                                std::string newTime = getValidatedStringInput("Enter new appointment time (HH:MM AM/PM): ");
                                
                                try {
                                    foundApp->rescheduleAppointment(newDate, newTime); // Call reschedule function
                                    std::cout << "Appointment ID " << appId << " rescheduled successfully." << std::endl;
                                } catch (const std::invalid_argument& e) {
                                    std::cerr << "Error rescheduling appointment: " << e.what() << std::endl;
                                }
                            } else {
                                std::cout << "Appointment with ID " << appId << " not found." << std::endl;
                            }
                            break;
                        }
                        case 3: // Back to Main Menu
                            break;
                        default:
                            std::cout << "Invalid choice. Please try again." << std::endl;
                            break;
                    }
                } while (subChoice != 3);
                break;

            case 4: // Display All Patients
                myHospital.displayAllPatients();
                break;

            case 5: // Display All Doctors
                myHospital.displayAllDoctors();
                break;

            case 6: // Display All Appointments
                myHospital.displayAllAppointments();
                break;

            case 7: // Exit
                std::cout << "Exiting Hospital Management System. Goodbye!" << std::endl;
                break;

            default:
                std::cout << "Invalid choice. Please enter a number between 1 and 7." << std::endl;
                break;
        }
    } while (choice != 7); // Continue until user chooses to exit (7)

    return 0;
}