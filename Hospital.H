#ifndef HOSPITAL_H
#define HOSPITAL_H

#include <iostream>
#include <vector>
#include <string>
#include <limits> // Required for numeric_limits
#include <fstream> // For file handling
#include <sstream> // For string streams

// Base class for common properties (e.g., ID, Name)
class Person {
protected:
    std::string id;
    std::string name;
    std::string phone;

public:
    Person(std::string id = "", std::string name = "", std::string phone = "")
        : id(id), name(name), phone(phone) {}

    virtual ~Person() = default;

    // Getters
    std::string getId() const { return id; }
    std::string getName() const { return name; }
    std::string getPhone() const { return phone; }

    // Setters
    void setId(const std::string& newId) { id = newId; }
    void setName(const std::string& newName) { name = newName; }
    void setPhone(const std::string& newPhone) { phone = newPhone; }

    virtual void display() const = 0; // Pure virtual for polymorphic display
    virtual std::string toString() const = 0; // For file saving
};

// Derived class for Patient
class Patient : public Person {
private:
    int age;
    std::string gender;
    std::string address;
    std::string medicalHistory; // Simple string for history

public:
    Patient(std::string id = "", std::string name = "", std::string phone = "", int age = 0,
            std::string gender = "", std::string address = "", std::string medicalHistory = "")
        : Person(id, name, phone), age(age), gender(gender), address(address), medicalHistory(medicalHistory) {}

    // Getters
    int getAge() const { return age; }
    std::string getGender() const { return gender; }
    std::string getAddress() const { return address; }
    std::string getMedicalHistory() const { return medicalHistory; }

    // Setters
    void setAge(int newAge) { age = newAge; }
    void setGender(const std::string& newGender) { gender = newGender; }
    void setAddress(const std::string& newAddress) { address = newAddress; }
    void setMedicalHistory(const std::string& newHistory) { medicalHistory = newHistory; }

    void display() const override {
        std::cout << "--- Patient Details ---" << std::endl;
        std::cout << "ID: " << id << std::endl;
        std::cout << "Name: " << name << std::endl;
        std::cout << "Phone: " << phone << std::endl;
        std::cout << "Age: " << age << std::endl;
        std::cout << "Gender: " << gender << std::endl;
        std::cout << "Address: " << address << std::endl;
        std::cout << "Medical History: " << medicalHistory << std::endl;
        std::cout << "-----------------------" << std::endl;
    }

    std::string toString() const override {
        std::ostringstream oss;
        oss << id << "|" << name << "|" << phone << "|" << age << "|" << gender << "|" << address << "|" << medicalHistory;
        return oss.str();
    }
};

// Derived class for Doctor
class Doctor : public Person {
private:
    std::string specialization;
    std::string licenseNumber;
    std::string workingHours; // e.g., "9:00 AM - 5:00 PM"

public:
    Doctor(std::string id = "", std::string name = "", std::string phone = "",
           std::string specialization = "", std::string licenseNumber = "", std::string workingHours = "")
        : Person(id, name, phone), specialization(specialization), licenseNumber(licenseNumber), workingHours(workingHours) {}

    // Getters
    std::string getSpecialization() const { return specialization; }
    std::string getLicenseNumber() const { return licenseNumber; }
    std::string getWorkingHours() const { return workingHours; }

    // Setters
    void setSpecialization(const std::string& newSpecialization) { specialization = newSpecialization; }
    void setLicenseNumber(const std::string& newLicenseNumber) { licenseNumber = newLicenseNumber; }
    void setWorkingHours(const std::string& newWorkingHours) { workingHours = newWorkingHours; }

    void display() const override {
        std::cout << "--- Doctor Details ---" << std::endl;
        std::cout << "ID: " << id << std::endl;
        std::cout << "Name: " << name << std::endl;
        std::cout << "Phone: " << phone << std::endl;
        std::cout << "Specialization: " << specialization << std::endl;
        std::cout << "License Number: " << licenseNumber << std::endl;
        std::cout << "Working Hours: " << workingHours << std::endl;
        std::cout << "----------------------" << std::endl;
    }

    std::string toString() const override {
        std::ostringstream oss;
        oss << id << "|" << name << "|" << phone << "|" << specialization << "|" << licenseNumber << "|" << workingHours;
        return oss.str();
    }
};

// Class for Appointment
class Appointment {
private:
    std::string appointmentId;
    std::string patientId;
    std::string doctorId;
    std::string date; // Format: YYYY-MM-DD
    std::string time; // Format: HH:MM

public:
    Appointment(std::string appId = "", std::string patId = "", std::string docId = "",
                std::string date = "", std::string time = "")
        : appointmentId(appId), patientId(patId), doctorId(docId), date(date), time(time) {}

    // Getters
    std::string getAppointmentId() const { return appointmentId; }
    std::string getPatientId() const { return patientId; }
    std::string getDoctorId() const { return doctorId; }
    std::string getDate() const { return date; }
    std::string getTime() const { return time; }

    // Setters
    void setDate(const std::string& newDate) { date = newDate; }
    void setTime(const std::string& newTime) { time = newTime; }

    void display() const {
        std::cout << "--- Appointment Details ---" << std::endl;
        std::cout << "Appointment ID: " << appointmentId << std::endl;
        std::cout << "Patient ID: " << patientId << std::endl;
        std::cout << "Doctor ID: " << doctorId << std::endl;
        std::cout << "Date: " << date << std::endl;
        std::cout << "Time: " << time << std::endl;
        std::cout << "---------------------------" << std::endl;
    }

    std::string toString() const {
        std::ostringstream oss;
        oss << appointmentId << "|" << patientId << "|" << doctorId << "|" << date << "|" << time;
        return oss.str();
    }
};

// Main Hospital Management System Class
class Hospital {
private:
    std::vector<Patient> patients;
    std::vector<Doctor> doctors;
    std::vector<Appointment> appointments;

    std::string generateUniqueId(const std::string& prefix) {
        // Simple unique ID generation based on time
        time_t timer;
        time(&timer);
        std::string uniqueId = prefix + std::to_string(timer);
        return uniqueId;
    }

    // Helper for input validation
    template<typename T>
    T getValidInput(const std::string& prompt) {
        T value;
        while (true) {
            std::cout << prompt;
            std::cin >> value;
            if (std::cin.fail()) {
                std::cout << "Invalid input. Please enter a valid number." << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            } else {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear rest of line
                return value;
            }
        }
    }

public:
    Hospital() {
        loadData(); // Load data when Hospital object is created
    }

    ~Hospital() {
        saveData(); // Save data when Hospital object is destroyed
    }

    // --- Patient Management ---
    void addPatient() {
        std::string id = generateUniqueId("PAT");
        std::string name, phone, gender, address, medicalHistory;
        int age;

        std::cout << "\n--- Add New Patient ---" << std::endl;
        std::cout << "Patient ID: " << id << std::endl;
        std::cout << "Enter Name: "; std::getline(std::cin, name);
        std::cout << "Enter Phone: "; std::getline(std::cin, phone);
        age = getValidInput<int>("Enter Age: ");
        std::cout << "Enter Gender: "; std::getline(std::cin, gender);
        std::cout << "Enter Address: "; std::getline(std::cin, address);
        std::cout << "Enter Medical History: "; std::getline(std::cin, medicalHistory);

        patients.emplace_back(id, name, phone, age, gender, address, medicalHistory);
        std::cout << "Patient added successfully!" << std::endl;
    }

    void displayAllPatients() const {
        if (patients.empty()) {
            std::cout << "No patients registered." << std::endl;
            return;
        }
        std::cout << "\n--- All Patients ---" << std::endl;
        for (const auto& pat : patients) {
            pat.display();
            std::cout << "\n";
        }
    }

    void searchPatient() const {
        std::string query;
        std::cout << "\n--- Search Patient ---" << std::endl;
        std::cout << "Enter Patient ID or Name: ";
        std::getline(std::cin, query);

        bool found = false;
        for (const auto& pat : patients) {
            if (pat.getId() == query || pat.getName().find(query) != std::string::npos) {
                pat.display();
                found = true;
                break;
            }
        }
        if (!found) {
            std::cout << "Patient not found." << std::endl;
        }
    }

    void updatePatient() {
        std::string id;
        std::cout << "\n--- Update Patient ---" << std::endl;
        std::cout << "Enter Patient ID to update: ";
        std::getline(std::cin, id);

        for (auto& pat : patients) {
            if (pat.getId() == id) {
                std::cout << "Patient found. Enter new details (leave blank to keep current)." << std::endl;
                std::string newName, newPhone, newGender, newAddress, newMedicalHistory, newAgeStr;
                int newAge;

                std::cout << "New Name (" << pat.getName() << "): "; std::getline(std::cin, newName);
                if (!newName.empty()) pat.setName(newName);

                std::cout << "New Phone (" << pat.getPhone() << "): "; std::getline(std::cin, newPhone);
                if (!newPhone.empty()) pat.setPhone(newPhone);
                
                std::cout << "New Age (" << pat.getAge() << "): "; std::getline(std::cin, newAgeStr);
                if (!newAgeStr.empty()) {
                    try {
                        newAge = std::stoi(newAgeStr);
                        pat.setAge(newAge);
                    } catch (const std::invalid_argument& e) {
                        std::cout << "Invalid age format. Age not updated." << std::endl;
                    } catch (const std::out_of_range& e) {
                        std::cout << "Age out of range. Age not updated." << std::endl;
                    }
                }

                std::cout << "New Gender (" << pat.getGender() << "): "; std::getline(std::cin, newGender);
                if (!newGender.empty()) pat.setGender(newGender);

                std::cout << "New Address (" << pat.getAddress() << "): "; std::getline(std::cin, newAddress);
                if (!newAddress.empty()) pat.setAddress(newAddress);

                std::cout << "New Medical History (" << pat.getMedicalHistory() << "): "; std::getline(std::cin, newMedicalHistory);
                if (!newMedicalHistory.empty()) pat.setMedicalHistory(newMedicalHistory);

                std::cout << "Patient updated successfully!" << std::endl;
                return;
            }
        }
        std::cout << "Patient with ID " << id << " not found." << std::endl;
    }

    void deletePatient() {
        std::string id;
        std::cout << "\n--- Delete Patient ---" << std::endl;
        std::cout << "Enter Patient ID to delete: ";
        std::getline(std::cin, id);

        auto it = patients.begin();
        while (it != patients.end()) {
            if (it->getId() == id) {
                it = patients.erase(it);
                std::cout << "Patient deleted successfully!" << std::endl;
                // Also delete any appointments related to this patient
                appointments.erase(std::remove_if(appointments.begin(), appointments.end(),
                                                  [&id](const Appointment& app){ return app.getPatientId() == id; }),
                                   appointments.end());
                return;
            } else {
                ++it;
            }
        }
        std::cout << "Patient with ID " << id << " not found." << std::endl;
    }

    // --- Doctor Management ---
    void addDoctor() {
        std::string id = generateUniqueId("DOC");
        std::string name, phone, specialization, licenseNumber, workingHours;

        std::cout << "\n--- Add New Doctor ---" << std::endl;
        std::cout << "Doctor ID: " << id << std::endl;
        std::cout << "Enter Name: "; std::getline(std::cin, name);
        std::cout << "Enter Phone: "; std::getline(std::cin, phone);
        std::cout << "Enter Specialization: "; std::getline(std::cin, specialization);
        std::cout << "Enter License Number: "; std::getline(std::cin, licenseNumber);
        std::cout << "Enter Working Hours (e.g., 9:00 AM - 5:00 PM): "; std::getline(std::cin, workingHours);

        doctors.emplace_back(id, name, phone, specialization, licenseNumber, workingHours);
        std::cout << "Doctor added successfully!" << std::endl;
    }

    void displayAllDoctors() const {
        if (doctors.empty()) {
            std::cout << "No doctors registered." << std::endl;
            return;
        }
        std::cout << "\n--- All Doctors ---" << std::endl;
        for (const auto& doc : doctors) {
            doc.display();
            std::cout << "\n";
        }
    }

    void searchDoctor() const {
        std::string query;
        std::cout << "\n--- Search Doctor ---" << std::endl;
        std::cout << "Enter Doctor ID, Name, or Specialization: ";
        std::getline(std::cin, query);

        bool found = false;
        for (const auto& doc : doctors) {
            if (doc.getId() == query || doc.getName().find(query) != std::string::npos || doc.getSpecialization().find(query) != std::string::npos) {
                doc.display();
                found = true;
                break;
            }
        }
        if (!found) {
            std::cout << "Doctor not found." << std::endl;
        }
    }

    void updateDoctor() {
        std::string id;
        std::cout << "\n--- Update Doctor ---" << std::endl;
        std::cout << "Enter Doctor ID to update: ";
        std::getline(std::cin, id);

        for (auto& doc : doctors) {
            if (doc.getId() == id) {
                std::cout << "Doctor found. Enter new details (leave blank to keep current)." << std::endl;
                std::string newName, newPhone, newSpecialization, newLicenseNumber, newWorkingHours;

                std::cout << "New Name (" << doc.getName() << "): "; std::getline(std::cin, newName);
                if (!newName.empty()) doc.setName(newName);

                std::cout << "New Phone (" << doc.getPhone() << "): "; std::getline(std::cin, newPhone);
                if (!newPhone.empty()) doc.setPhone(newPhone);

                std::cout << "New Specialization (" << doc.getSpecialization() << "): "; std::getline(std::cin, newSpecialization);
                if (!newSpecialization.empty()) doc.setSpecialization(newSpecialization);

                std::cout << "New License Number (" << doc.getLicenseNumber() << "): "; std::getline(std::cin, newLicenseNumber);
                if (!newLicenseNumber.empty()) doc.setLicenseNumber(newLicenseNumber);

                std::cout << "New Working Hours (" << doc.getWorkingHours() << "): "; std::getline(std::cin, newWorkingHours);
                if (!newWorkingHours.empty()) doc.setWorkingHours(newWorkingHours);

                std::cout << "Doctor updated successfully!" << std::endl;
                return;
            }
        }
        std::cout << "Doctor with ID " << id << " not found." << std::endl;
    }

    void deleteDoctor() {
        std::string id;
        std::cout << "\n--- Delete Doctor ---" << std::endl;
        std::cout << "Enter Doctor ID to delete: ";
        std::getline(std::cin, id);

        auto it = doctors.begin();
        while (it != doctors.end()) {
            if (it->getId() == id) {
                it = doctors.erase(it);
                std::cout << "Doctor deleted successfully!" << std::endl;
                // Also delete any appointments related to this doctor
                appointments.erase(std::remove_if(appointments.begin(), appointments.end(),
                                                  [&id](const Appointment& app){ return app.getDoctorId() == id; }),
                                   appointments.end());
                return;
            } else {
                ++it;
            }
        }
        std::cout << "Doctor with ID " << id << " not found." << std::endl;
    }

    // --- Appointment Management ---
    void addAppointment() {
        std::string appId = generateUniqueId("APP");
        std::string patId, docId, date, time;

        std::cout << "\n--- Add New Appointment ---" << std::endl;
        std::cout << "Appointment ID: " << appId << std::endl;

        std::cout << "Enter Patient ID: "; std::getline(std::cin, patId);
        // Check if patient exists
        bool patientExists = false;
        for (const auto& pat : patients) {
            if (pat.getId() == patId) {
                patientExists = true;
                break;
            }
        }
        if (!patientExists) {
            std::cout << "Patient with ID " << patId << " not found. Cannot book appointment." << std::endl;
            return;
        }

        std::cout << "Enter Doctor ID: "; std::getline(std::cin, docId);
        // Check if doctor exists
        bool doctorExists = false;
        for (const auto& doc : doctors) {
            if (doc.getId() == docId) {
                doctorExists = true;
                break;
            }
        }
        if (!doctorExists) {
            std::cout << "Doctor with ID " << docId << " not found. Cannot book appointment." << std::endl;
            return;
        }

        std::cout << "Enter Date (YYYY-MM-DD): "; std::getline(std::cin, date);
        std::cout << "Enter Time (HH:MM): "; std::getline(std::cin, time);

        appointments.emplace_back(appId, patId, docId, date, time);
        std::cout << "Appointment added successfully!" << std::endl;
    }

    void displayAppointmentsForDoctor() const {
        std::string docId;
        std::cout << "\n--- Appointments for Doctor ---" << std::endl;
        std::cout << "Enter Doctor ID: ";
        std::getline(std::cin, docId);

        bool found = false;
        std::cout << "\nAppointments for Doctor ID: " << docId << std::endl;
        for (const auto& app : appointments) {
            if (app.getDoctorId() == docId) {
                app.display();
                found = true;
                std::cout << "\n";
            }
        }
        if (!found) {
            std::cout << "No appointments found for Doctor ID " << docId << "." << std::endl;
        }
    }

    void displayAppointmentsForPatient() const {
        std::string patId;
        std::cout << "\n--- Appointments for Patient ---" << std::endl;
        std::cout << "Enter Patient ID: ";
        std::getline(std::cin, patId);

        bool found = false;
        std::cout << "\nAppointments for Patient ID: " << patId << std::endl;
        for (const auto& app : appointments) {
            if (app.getPatientId() == patId) {
                app.display();
                found = true;
                std::cout << "\n";
            }
        }
        if (!found) {
            std::cout << "No appointments found for Patient ID " << patId << "." << std::endl;
        }
    }

    void searchAppointment() const {
        std::string query;
        std::cout << "\n--- Search Appointment ---" << std::endl;
        std::cout << "Enter Appointment ID or Date (YYYY-MM-DD): ";
        std::getline(std::cin, query);

        bool found = false;
        for (const auto& app : appointments) {
            if (app.getAppointmentId() == query || app.getDate() == query) {
                app.display();
                found = true;
                break;
            }
        }
        if (!found) {
            std::cout << "Appointment not found." << std::endl;
        }
    }

    void updateAppointment() {
        std::string appId;
        std::cout << "\n--- Update Appointment ---" << std::endl;
        std::cout << "Enter Appointment ID to update: ";
        std::getline(std::cin, appId);

        for (auto& app : appointments) {
            if (app.getAppointmentId() == appId) {
                std::cout << "Appointment found. Enter new details (leave blank to keep current)." << std::endl;
                std::string newDate, newTime;

                std::cout << "New Date (" << app.getDate() << "): "; std::getline(std::cin, newDate);
                if (!newDate.empty()) app.setDate(newDate);

                std::cout << "New Time (" << app.getTime() << "): "; std::getline(std::cin, newTime);
                if (!newTime.empty()) app.setTime(newTime);

                std::cout << "Appointment updated successfully!" << std::endl;
                return;
            }
        }
        std::cout << "Appointment with ID " << appId << " not found." << std::endl;
    }

    void deleteAppointment() {
        std::string appId;
        std::cout << "\n--- Delete Appointment ---" << std::endl;
        std::cout << "Enter Appointment ID to delete: ";
        std::getline(std::cin, appId);

        auto it = appointments.begin();
        while (it != appointments.end()) {
            if (it->getAppointmentId() == appId) {
                it = appointments.erase(it);
                std::cout << "Appointment deleted successfully!" << std::endl;
                return;
            } else {
                ++it;
            }
        }
        std::cout << "Appointment with ID " << appId << " not found." << std::endl;
    }

    // --- Reports (Basic examples) ---
    void generatePatientListReport() const {
        std::cout << "\n--- Patient List Report ---" << std::endl;
        if (patients.empty()) {
            std::cout << "No patients to report." << std::endl;
            return;
        }
        std::cout << "ID\tName\t\tAge\tGender\tPhone" << std::endl;
        std::cout << "----------------------------------------------------" << std::endl;
        for (const auto& pat : patients) {
            std::cout << pat.getId() << "\t" << pat.getName().substr(0,10) << "...\t" << pat.getAge() << "\t" << pat.getGender() << "\t" << pat.getPhone() << std::endl;
        }
        std::cout << "----------------------------------------------------" << std::endl;
    }

    void generateDoctorListReport() const {
        std::cout << "\n--- Doctor List Report ---" << std::endl;
        if (doctors.empty()) {
            std::cout << "No doctors to report." << std::endl;
            return;
        }
        std::cout << "ID\tName\t\tSpecialization\tPhone" << std::endl;
        std::cout << "----------------------------------------------------" << std::endl;
        for (const auto& doc : doctors) {
            std::cout << doc.getId() << "\t" << doc.getName().substr(0,10) << "...\t" << doc.getSpecialization().substr(0,12) << "...\t" << doc.getPhone() << std::endl;
        }
        std::cout << "----------------------------------------------------" << std::endl;
    }
    
    void generateDailyAppointmentsReport() const {
        std::string todayDate; // In a real system, you'd get current date
        std::cout << "\n--- Daily Appointments Report ---" << std::endl;
        std::cout << "Enter Date for Report (YYYY-MM-DD): ";
        std::getline(std::cin, todayDate);

        bool found = false;
        std::cout << "\nAppointments for " << todayDate << ":" << std::endl;
        for (const auto& app : appointments) {
            if (app.getDate() == todayDate) {
                std::cout << "App ID: " << app.getAppointmentId() << ", Patient ID: " << app.getPatientId()
                          << ", Doctor ID: " << app.getDoctorId() << ", Time: " << app.getTime() << std::endl;
                found = true;
            }
        }
        if (!found) {
            std::cout << "No appointments scheduled for " << todayDate << "." << std::endl;
        }
    }


    // --- File Handling (Persistence) ---
    void saveData() const {
        std::ofstream patientFile("patients.txt");
        if (patientFile.is_open()) {
            for (const auto& pat : patients) {
                patientFile << pat.toString() << std::endl;
            }
            patientFile.close();
        } else {
            std::cerr << "Error: Unable to open patients.txt for writing." << std::endl;
        }

        std::ofstream doctorFile("doctors.txt");
        if (doctorFile.is_open()) {
            for (const auto& doc : doctors) {
                doctorFile << doc.toString() << std::endl;
            }
            doctorFile.close();
        } else {
            std::cerr << "Error: Unable to open doctors.txt for writing." << std::endl;
        }

        std::ofstream appointmentFile("appointments.txt");
        if (appointmentFile.is_open()) {
            for (const auto& app : appointments) {
                appointmentFile << app.toString() << std::endl;
            }
            appointmentFile.close();
        } else {
            std::cerr << "Error: Unable to open appointments.txt for writing." << std::endl;
        }
        std::cout << "Data saved successfully." << std::endl;
    }

    void loadData() {
        // Load Patients
        std::ifstream patientFile("patients.txt");
        if (patientFile.is_open()) {
            std::string line;
            while (std::getline(patientFile, line)) {
                std::stringstream ss(line);
                std::string id, name, phone, gender, address, medicalHistory, ageStr;
                int age;

                std::getline(ss, id, '|');
                std::getline(ss, name, '|');
                std::getline(ss, phone, '|');
                std::getline(ss, ageStr, '|');
                age = std::stoi(ageStr);
                std::getline(ss, gender, '|');
                std::getline(ss, address, '|');
                std::getline(ss, medicalHistory, '|');
                patients.emplace_back(id, name, phone, age, gender, address, medicalHistory);
            }
            patientFile.close();
        } else {
            std::cout << "No existing patients.txt found or unable to open. Starting fresh." << std::endl;
        }

        // Load Doctors
        std::ifstream doctorFile("doctors.txt");
        if (doctorFile.is_open()) {
            std::string line;
            while (std::getline(doctorFile, line)) {
                std::stringstream ss(line);
                std::string id, name, phone, specialization, licenseNumber, workingHours;

                std::getline(ss, id, '|');
                std::getline(ss, name, '|');
                std::getline(ss, phone, '|');
                std::getline(ss, specialization, '|');
                std::getline(ss, licenseNumber, '|');
                std::getline(ss, workingHours, '|');
                doctors.emplace_back(id, name, phone, specialization, licenseNumber, workingHours);
            }
            doctorFile.close();
        } else {
            std::cout << "No existing doctors.txt found or unable to open. Starting fresh." << std::endl;
        }

        // Load Appointments
        std::ifstream appointmentFile("appointments.txt");
        if (appointmentFile.is_open()) {
            std::string line;
            while (std::getline(appointmentFile, line)) {
                std::stringstream ss(line);
                std::string appId, patId, docId, date, time;

                std::getline(ss, appId, '|');
                std::getline(ss, patId, '|');
                std::getline(ss, docId, '|');
                std::getline(ss, date, '|');
                std::getline(ss, time, '|');
                appointments.emplace_back(appId, patId, docId, date, time);
            }
            appointmentFile.close();
        } else {
            std::cout << "No existing appointments.txt found or unable to open. Starting fresh." << std::endl;
        }
        std::cout << "Data loaded successfully (if files existed)." << std::endl;
    }
};

#endif // HOSPITAL_H













































/*#ifndef HOSPITAL_H
#define HOSPITAL_H

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// ======== Class Person ========
class Person {
protected:
    string name;
    int age;
public:
    Person(string n, int a) : name(n), age(a) {}
    virtual void displayInfo() {
        cout << "Name: " << name << "\nAge: " << age << endl;
    }
    string getName() const { return name; }
};

// ======== Class Patient ========
class Patient : public Person {
    string disease;
    int patientID;
public:
    Patient(string n, int a, string d, int id)
        : Person(n, a), disease(d), patientID(id) {}

    void displayInfo() override {
        cout << "[Patient Info]\n";
        Person::displayInfo();
        cout << "Disease: " << disease << "\nPatient ID: " << patientID << endl;
    }

    int getID() const { return patientID; }
};

// ======== Class Doctor ========
class Doctor : public Person {
    string specialization;
    int doctorID;
public:
    Doctor(string n, int a, string s, int id)
        : Person(n, a), specialization(s), doctorID(id) {}

    void displayInfo() override {
        cout << "[Doctor Info]\n";
        Person::displayInfo();
        cout << "Specialization: " << specialization << "\nDoctor ID: " << doctorID << endl;
    }

    int getID() const { return doctorID; }
};

// ======== Class Appointment ========
class Appointment {
    int appointmentID;
    int patientID;
    int doctorID;
    string date;
    string time;
public:
    Appointment(int aID, int pID, int dID, string dt, string tm)
        : appointmentID(aID), patientID(pID), doctorID(dID), date(dt), time(tm) {}

    void displayInfo() {
        cout << "[Appointment Info]\n";
        cout << "Appointment ID: " << appointmentID << endl;
        cout << "Patient ID: " << patientID << endl;
        cout << "Doctor ID: " << doctorID << endl;
        cout << "Date: " << date << " | Time: " << time << endl;
    }
};

// ======== Class Hospital ========
class Hospital {
    string hospitalName;
    vector<Patient> patients;
    vector<Doctor> doctors;
    vector<Appointment> appointments;

public:
    Hospital(string name) : hospitalName(name) {}

    void addPatient(const Patient &p) {
        patients.push_back(p);
        cout << "✅ Patient added successfully!\n";
    }

    void addDoctor(const Doctor &d) {
        doctors.push_back(d);
        cout << "✅ Doctor added successfully!\n";
    }

    void addAppointment() {
        if (patients.empty() || doctors.empty()) {
            cout << "⚠️ You must have at least one patient and one doctor before scheduling an appointment!\n";
            return;
        }

        int aID, pID, dID;
        string date, time;

        cout << "Enter Appointment ID: ";
        cin >> aID; cin.ignore();
        cout << "Enter Patient ID: ";
        cin >> pID; cin.ignore();
        cout << "Enter Doctor ID: ";
        cin >> dID; cin.ignore();
        cout << "Enter Date (e.g., 2025-10-13): ";
        getline(cin, date);
        cout << "Enter Time (e.g., 14:30): ";
        getline(cin, time);

        appointments.emplace_back(aID, pID, dID, date, time);
        cout << "✅ Appointment scheduled successfully!\n";
    }

    void showAllPatients() {
        if (patients.empty()) { cout << "No patients found.\n"; return; }
        cout << "\n--- Patient List ---\n";
        for (auto &p : patients)
            p.displayInfo();
    }

    void showAllDoctors() {
        if (doctors.empty()) { cout << "No doctors found.\n"; return; }
        cout << "\n--- Doctor List ---\n";
        for (auto &d : doctors)
            d.displayInfo();
    }

    void showAllAppointments() {
        if (appointments.empty()) { cout << "No appointments found.\n"; return; }
        cout << "\n--- Appointment List ---\n";
        for (auto &a : appointments)
            a.displayInfo();
    }

    void menu() {
        int choice;
        while (true) {
            cout << "\n=== " << hospitalName << " Management System ===" << endl;
            cout << "1. Add Patient\n2. Add Doctor\n3. Show All Patients\n4. Show All Doctors\n";
            cout << "5. Schedule Appointment\n6. Show All Appointments\n0. Exit\nChoice: ";
            cin >> choice;
            cin.ignore();

            if (choice == 0) break;
            switch (choice) {
            case 1: {
                string name, disease; int age, id;
                cout << "Enter Patient Name: "; getline(cin, name);
                cout << "Enter Age: "; cin >> age; cin.ignore();
                cout << "Enter Disease: "; getline(cin, disease);
                cout << "Enter Patient ID: "; cin >> id; cin.ignore();
                addPatient(Patient(name, age, disease, id));
                break;
            }
            case 2: {
                string name, spec; int age, id;
                cout << "Enter Doctor Name: "; getline(cin, name);
                cout << "Enter Age: "; cin >> age; cin.ignore();
                cout << "Enter Specialization: "; getline(cin, spec);
                cout << "Enter Doctor ID: "; cin >> id; cin.ignore();
                addDoctor(Doctor(name, age, spec, id));
                break;
            }
            case 3: showAllPatients(); break;
            case 4: showAllDoctors(); break;
            case 5: addAppointment(); break;
            case 6: showAllAppointments(); break;
            default: cout << "❌ Invalid choice!\n";
            }
        }
    }
};

#endif
*/