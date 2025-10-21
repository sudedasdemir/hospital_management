#include "Hospital.h" // Include the header file with all class definitions
#include <ctime>      // For time-based ID generation (in Hospital.h)

// Function to clear screen (platform specific)
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Function to display the main menu
void displayMainMenu() {
    clearScreen();
    std::cout << "\n==========================================" << std::endl;
    std::cout << "   HOSPITAL MANAGEMENT SYSTEM - MAIN MENU" << std::endl;
    std::cout << "==========================================" << std::endl;
    std::cout << "1. Patient Management" << std::endl;
    std::cout << "2. Doctor Management" << std::endl;
    std::cout << "3. Appointment Management" << std::endl;
    std::cout << "4. Reports" << std::endl;
    std::cout << "5. Exit" << std::endl;
    std::cout << "Enter your choice: ";
}

// Function to display Patient Management menu
void displayPatientMenu() {
    clearScreen();
    std::cout << "\n===============================" << std::endl;
    std::cout << "   PATIENT MANAGEMENT" << std::endl;
    std::cout << "===============================" << std::endl;
    std::cout << "1. Add New Patient" << std::endl;
    std::cout << "2. Display All Patients" << std::endl;
    std::cout << "3. Search Patient" << std::endl;
    std::cout << "4. Update Patient" << std::endl;
    std::cout << "5. Delete Patient" << std::endl;
    std::cout << "6. Back to Main Menu" << std::endl;
    std::cout << "Enter your choice: ";
}

// Function to display Doctor Management menu
void displayDoctorMenu() {
    clearScreen();
    std::cout << "\n===============================" << std::endl;
    std::cout << "   DOCTOR MANAGEMENT" << std::endl;
    std::cout << "===============================" << std::endl;
    std::cout << "1. Add New Doctor" << std::endl;
    std::cout << "2. Display All Doctors" << std::endl;
    std::cout << "3. Search Doctor" << std::endl;
    std::cout << "4. Update Doctor" << std::endl;
    std::cout << "5. Delete Doctor" << std::endl;
    std::cout << "6. Back to Main Menu" << std::endl;
    std::cout << "Enter your choice: ";
}

// Function to display Appointment Management menu
void displayAppointmentMenu() {
    clearScreen();
    std::cout << "\n==================================" << std::endl;
    std::cout << "   APPOINTMENT MANAGEMENT" << std::endl;
    std::cout << "==================================" << std::endl;
    std::cout << "1. Book New Appointment" << std::endl;
    std::cout << "2. Display Appointments for Doctor" << std::endl;
    std::cout << "3. Display Appointments for Patient" << std::endl;
    std::cout << "4. Search Appointment" << std::endl;
    std::cout << "5. Update Appointment" << std::endl;
    std::cout << "6. Cancel Appointment" << std::endl;
    std::cout << "7. Back to Main Menu" << std::endl;
    std::cout << "Enter your choice: ";
}

// Function to display Reports menu
void displayReportsMenu() {
    clearScreen();
    std::cout << "\n===============================" << std::endl;
    std::cout << "   REPORTS MENU" << std::endl;
    std::cout << "===============================" << std::endl;
    std::cout << "1. Generate Patient List Report" << std::endl;
    std::cout << "2. Generate Doctor List Report" << std::endl;
    std::cout << "3. Generate Daily Appointments Report" << std::endl;
    std::cout << "4. Back to Main Menu" << std::endl;
    std::cout << "Enter your choice: ";
}


int main() {
    Hospital hospital; // Create a Hospital object, which will load data

    std::string choice_str;
    int choice;

    while (true) {
        displayMainMenu();
        std::getline(std::cin, choice_str);
        try {
            choice = std::stoi(choice_str);
        } catch (const std::invalid_argument& e) {
            choice = 0; // Invalid input
        } catch (const std::out_of_range& e) {
            choice = 0; // Input too large
        }

        switch (choice) {
            case 1: { // Patient Management
                int pat_choice;
                while (true) {
                    displayPatientMenu();
                    std::getline(std::cin, choice_str);
                    try {
                        pat_choice = std::stoi(choice_str);
                    } catch (const std::invalid_argument& e) {
                        pat_choice = 0;
                    } catch (const std::out_of_range& e) {
                        pat_choice = 0;
                    }

                    switch (pat_choice) {
                        case 1: hospital.addPatient(); break;
                        case 2: hospital.displayAllPatients(); break;
                        case 3: hospital.searchPatient(); break;
                        case 4: hospital.updatePatient(); break;
                        case 5: hospital.deletePatient(); break;
                        case 6: goto end_patient_menu;
                        default: std::cout << "Invalid choice. Please try again." << std::endl; break;
                    }
                    std::cout << "\nPress Enter to continue...";
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Wait for user input
                }
                end_patient_menu:;
                break;
            }
            case 2: { // Doctor Management
                int doc_choice;
                while (true) {
                    displayDoctorMenu();
                    std::getline(std::cin, choice_str);
                    try {
                        doc_choice = std::stoi(choice_str);
                    } catch (const std::invalid_argument& e) {
                        doc_choice = 0;
                    } catch (const std::out_of_range& e) {
                        doc_choice = 0;
                    }
                    switch (doc_choice) {
                        case 1: hospital.addDoctor(); break;
                        case 2: hospital.displayAllDoctors(); break;
                        case 3: hospital.searchDoctor(); break;
                        case 4: hospital.updateDoctor(); break;
                        case 5: hospital.deleteDoctor(); break;
                        case 6: goto end_doctor_menu;
                        default: std::cout << "Invalid choice. Please try again." << std::endl; break;
                    }
                    std::cout << "\nPress Enter to continue...";
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                end_doctor_menu:;
                break;
            }
            case 3: { // Appointment Management
                int app_choice;
                while (true) {
                    displayAppointmentMenu();
                    std::getline(std::cin, choice_str);
                    try {
                        app_choice = std::stoi(choice_str);
                    } catch (const std::invalid_argument& e) {
                        app_choice = 0;
                    } catch (const std::out_of_range& e) {
                        app_choice = 0;
                    }
                    switch (app_choice) {
                        case 1: hospital.addAppointment(); break;
                        case 2: hospital.displayAppointmentsForDoctor(); break;
                        case 3: hospital.displayAppointmentsForPatient(); break;
                        case 4: hospital.searchAppointment(); break;
                        case 5: hospital.updateAppointment(); break;
                        case 6: hospital.deleteAppointment(); break;
                        case 7: goto end_appointment_menu;
                        default: std::cout << "Invalid choice. Please try again." << std::endl; break;
                    }
                    std::cout << "\nPress Enter to continue...";
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                end_appointment_menu:;
                break;
            }
            case 4: { // Reports
                int rep_choice;
                while (true) {
                    displayReportsMenu();
                    std::getline(std::cin, choice_str);
                    try {
                        rep_choice = std::stoi(choice_str);
                    } catch (const std::invalid_argument& e) {
                        rep_choice = 0;
                    } catch (const std::out_of_range& e) {
                        rep_choice = 0;
                    }
                    switch (rep_choice) {
                        case 1: hospital.generatePatientListReport(); break;
                        case 2: hospital.generateDoctorListReport(); break;
                        case 3: hospital.generateDailyAppointmentsReport(); break;
                        case 4: goto end_reports_menu;
                        default: std::cout << "Invalid choice. Please try again." << std::endl; break;
                    }
                    std::cout << "\nPress Enter to continue...";
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                end_reports_menu:;
                break;
            }
            case 5:
                hospital.saveData(); // Save data before exiting
                std::cout << "Exiting Hospital Management System. Goodbye!" << std::endl;
                return 0;
            default:
                std::cout << "Invalid choice. Please enter a number between 1 and 5." << std::endl;
                std::cout << "\nPress Enter to continue...";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                break;
        }
    }

    return 0;
}
















































/*#include <iostream>
#include "Hospital.h"   // All the class definitions
using namespace std;

int main() {
    Hospital h("City Hospital");
    h.menu();   // open the main menu
    cout << "\nExiting the system...\n";
    return 0;
}
*/