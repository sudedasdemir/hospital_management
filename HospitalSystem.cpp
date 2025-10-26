#include <iostream>
#include <stdexcept>
#include <algorithm> // For std::transform
#include <cctype>    // For ::tolower
#include <memory>    // For std::shared_ptr

#include "HospitalSystem.h" // Include the combined header

// --- Person Class Implementation ---
// Constructor implementation: initializes members using setters for validation
Person::Person(const std::string& _name, int _age, const std::string& _gender) {
    setName(_name);
    setAge(_age);
    setGender(_gender);
}

// Destructor (can be used for debugging object destruction)
Person::~Person() {
    // std::cout << "Person " << name << " destroyed." << std::endl;
}

// Setter for name with validation
void Person::setName(const std::string& _name) {
    if (_name.empty()) {
        throw std::invalid_argument("Name cannot be empty!");
    }
    name = _name;
}

// Setter for age with validation
void Person::setAge(int _age) {
    if (_age < 0 || _age > 120) {
        throw std::invalid_argument("Invalid age!");
    }
    age = _age;
}

// Setter for gender with validation and default to 'Unknown'
void Person::setGender(const std::string& _gender) {
    if (_gender != "Male" && _gender != "Female" && _gender != "Unknown") {
        std::cout << "Warning: Invalid gender specified. Setting to 'Unknown'." << std::endl;
        gender = "Unknown";
    } else {
        gender = _gender;
    }
}

// Getters for Person attributes
std::string Person::getName() const {
    return name;
}

int Person::getAge() const {
    return age;
}

std::string Person::getGender() const {
    return gender;
}

// Displays basic Person information
void Person::displayInfo() const {
    std::cout << "Name: " << name << ", Age: " << age << ", Gender: " << gender;
}

// --- Patient Class Implementation ---
// Initialize static member for patient ID generation
int Patient::nextPatientID = 1001; // Starting patient IDs from 1001

// Patient constructor, calls base class constructor and sets Patient-specific members
Patient::Patient(const std::string& _name, int _age, const std::string& _gender,
                 const std::string& _disease, int _patientID)
    : Person(_name, _age, _gender) { // Call Person's constructor
    if (_patientID == 0) { // If _patientID is 0, generate a new one
        setPatientID(nextPatientID++);
    } else { // Otherwise, use the provided ID
        setPatientID(_patientID);
    }
    setDisease(_disease);
}

// Destructor
Patient::~Patient() {
    // std::cout << "Patient " << getName() << " destroyed." << std::endl;
}

// Setter for patient ID with validation
void Patient::setPatientID(int _patientID) {
    if (_patientID <= 0) {
        throw std::invalid_argument("Patient ID must be positive!");
    }
    patientID = _patientID;
}

// Setter for disease
void Patient::setDisease(const std::string& _disease) {
    disease = _disease;
}

// Adds a medical record to the patient's history
void Patient::addMedicalRecord(const std::string& record) {
    if (record.empty()) {
        throw std::invalid_argument("Medical record cannot be empty!");
    }
    medicalHistory.push_back(record);
    std::cout << "Medical record added for patient " << getName() << "." << std::endl;
}

// Displays the patient's full medical history
void Patient::displayMedicalHistory() const {
    if (medicalHistory.empty()) {
        std::cout << "No medical history available for " << getName() << "." << std::endl;
        return;
    }
    std::cout << "--- Medical History for " << getName() << " (ID: " << patientID << ") ---" << std::endl;
    for (size_t i = 0; i < medicalHistory.size(); ++i) {
        std::cout << "  " << (i + 1) << ". " << medicalHistory[i] << std::endl;
    }
    std::cout << "---------------------------------------" << std::endl;
}

// Getters for Patient attributes
int Patient::getPatientID() const {
    return patientID;
}

std::string Patient::getDisease() const {
    return disease;
}

const std::vector<std::string>& Patient::getMedicalHistory() const {
    return medicalHistory;
}

// Overridden displayInfo to include Patient-specific details
void Patient::displayInfo() const {
    Person::displayInfo(); // Call base class displayInfo
    std::cout << ", Patient ID: " << patientID << ", Disease: " << disease << std::endl;
}

// --- Doctor Class Implementation ---
// Initialize static member for doctor ID generation
int Doctor::nextDoctorID = 2001; // Starting doctor IDs from 2001

// Doctor constructor, calls base class constructor and sets Doctor-specific members
Doctor::Doctor(const std::string& _name, int _age, const std::string& _gender,
               const std::string& _specialization, int _licenseNumber)
    : Person(_name, _age, _gender) { // Call Person's constructor
    setDoctorID(nextDoctorID++); // Assign unique ID
    setSpecialization(_specialization);
    setLicenseNumber(_licenseNumber);
}

// Destructor
Doctor::~Doctor() {
    // std::cout << "Doctor " << getName() << " destroyed." << std::endl;
}

// Setter for doctor ID with validation
void Doctor::setDoctorID(int _doctorID) {
    if (_doctorID <= 0) {
        throw std::invalid_argument("Doctor ID must be positive!");
    }
    doctorID = _doctorID;
}

// Setter for specialization with validation
void Doctor::setSpecialization(const std::string& _specialization) {
    if (_specialization.empty()) {
        throw std::invalid_argument("Specialization cannot be empty!");
    }
    specialization = _specialization;
}

// Setter for license number with basic validation
void Doctor::setLicenseNumber(int _licenseNumber) {
    if (_licenseNumber <= 0) {
        std::cout << "Warning: Invalid license number. Setting to 0." << std::endl;
        licenseNumber = 0;
    } else {
        licenseNumber = _licenseNumber;
    }
}

// Updates the doctor's specialization
void Doctor::updateSpecialization(const std::string& newSpecialization) {
    setSpecialization(newSpecialization); // Uses setter for validation
    std::cout << "Doctor " << getName() << "'s specialization updated to " << newSpecialization << "." << std::endl;
}

// Getters for Doctor attributes
int Doctor::getDoctorID() const {
    return doctorID;
}

std::string Doctor::getSpecialization() const {
    return specialization;
}

int Doctor::getLicenseNumber() const {
    return licenseNumber;
}

// Overridden displayInfo to include Doctor-specific details
void Doctor::displayInfo() const {
    Person::displayInfo(); // Call base class displayInfo
    std::cout << ", Doctor ID: " << doctorID << ", Specialization: " << specialization
              << ", License: " << licenseNumber << std::endl;
}

// --- Appointment Class Implementation ---
// Initialize static member for appointment ID generation
int Appointment::nextAppointmentID = 3001; // Starting appointment IDs from 3001

// Appointment constructor, takes shared_ptr for Patient and Doctor for composition
Appointment::Appointment(int _appointmentID, const std::string& _date, const std::string& _time,
                         std::shared_ptr<Patient> _patient, std::shared_ptr<Doctor> _doctor) {
    if (_appointmentID == 0) { // If _appointmentID is 0, generate a new one
        setAppointmentID(nextAppointmentID++);
    } else { // Otherwise, use the provided ID
        setAppointmentID(_appointmentID);
    }
    setDate(_date);
    setTime(_time);
    patient = _patient; // Assign shared_ptr to patient
    doctor = _doctor;   // Assign shared_ptr to doctor
    setStatus("Booked");
}

// Destructor
Appointment::~Appointment() {
    // std::cout << "Appointment " << appointmentID << " destroyed." << std::endl;
}

// Setter for appointment ID with validation
void Appointment::setAppointmentID(int _appointmentID) {
    if (_appointmentID <= 0) {
        throw std::invalid_argument("Appointment ID must be positive!");
    }
    appointmentID = _appointmentID;
}

// Setter for date with validation
void Appointment::setDate(const std::string& _date) {
    if (_date.empty()) {
        throw std::invalid_argument("Date cannot be empty!");
    }
    date = _date;
}

// Setter for time with validation
void Appointment::setTime(const std::string& _time) {
    if (_time.empty()) {
        throw std::invalid_argument("Time cannot be empty!");
    }
    time = _time;
}

// Setter for status
void Appointment::setStatus(const std::string& _status) {
    status = _status;
}

// Getters for Appointment attributes
int Appointment::getAppointmentID() const {
    return appointmentID;
}

std::string Appointment::getDate() const {
    return date;
}

std::string Appointment::getTime() const {
    return time;
}

std::string Appointment::getStatus() const {
    return status;
}

// Getter for the associated Patient (shared_ptr)
std::shared_ptr<Patient> Appointment::getPatient() const {
    return patient;
}

// Getter for the associated Doctor (shared_ptr)
std::shared_ptr<Doctor> Appointment::getDoctor() const {
    return doctor;
}

// Function to reschedule an appointment with a new date and time
void Appointment::rescheduleAppointment(const std::string& newDate, const std::string& newTime) {
    if (newDate.empty() || newTime.empty()) {
        throw std::invalid_argument("New date and time for reschedule cannot be empty!");
    }
    setDate(newDate); // uses the existing setDate to validate and set
    setTime(newTime); // uses the existing setTime to validate and set
    setStatus("Rescheduled");
    std::cout << "Appointment " << appointmentID << " rescheduled to " << date
              << " at " << time << "." << std::endl;
}

// Overloaded reschedule function: new date and time
void Appointment::reschedule(const std::string& newDate, const std::string& newTime) {
    if (newDate.empty() || newTime.empty()) {
        throw std::invalid_argument("New date and time for reschedule cannot be empty!");
    }
    setDate(newDate);
    setTime(newTime);
    setStatus("Rescheduled");
    std::cout << "Appointment " << appointmentID << " rescheduled to " << date
              << " at " << time << "." << std::endl;
}

// Overloaded reschedule function: new date only
void Appointment::reschedule(const std::string& newDate) {
    if (newDate.empty()) {
        throw std::invalid_argument("New date for reschedule cannot be empty!");
    }
    setDate(newDate);
    // Keep the current time as is
    setStatus("Rescheduled");
    std::cout << "Appointment " << appointmentID << " rescheduled to " << date
              << " (time remains " << time << ")." << std::endl;
}

// Displays comprehensive appointment information
void Appointment::displayInfo() const {
    std::cout << "Appointment ID: " << appointmentID
              << ", Date: " << date << ", Time: " << time
              << ", Status: " << status << std::endl;
    if (patient) { // Check if patient pointer is valid
        std::cout << "  Patient: " << patient->getName() << " (ID: " << patient->getPatientID() << ")";
    }
    if (doctor) { // Check if doctor pointer is valid
        std::cout << ", Doctor: " << doctor->getName() << " (Specialization: " << doctor->getSpecialization() << ")";
    }
    std::cout << std::endl;
}

// --- Hospital Class Implementation ---
// Adds a new patient to the hospital's patient list
void Hospital::addPatient(std::shared_ptr<Patient> patient) {
    patients.push_back(patient);
    std::cout << "Patient " << patient->getName() << " added." << std::endl;
}

// Adds a new doctor to the hospital's doctor list
void Hospital::addDoctor(std::shared_ptr<Doctor> doctor) {
    doctors.push_back(doctor);
    std::cout << "Doctor " << doctor->getName() << " added." << std::endl;
}

// Adds a new appointment to the hospital's appointment list
void Hospital::addAppointment(std::shared_ptr<Appointment> appointment) {
    appointments.push_back(appointment);
    std::cout << "Appointment " << appointment->getAppointmentID() << " added." << std::endl;
}

// Searches for a patient by ID
std::shared_ptr<Patient> Hospital::searchPatient(int patientID) const {
    for (const auto& p : patients) {
        if (p->getPatientID() == patientID) {
            return p; // Found patient, return shared_ptr
        }
    }
    return nullptr; // Patient not found
}

// Searches for a patient by name, with case-sensitive option
std::shared_ptr<Patient> Hospital::searchPatient(const std::string& patientName, bool caseSensitive) const {
    for (const auto& p : patients) {
        if (caseSensitive) {
            if (p->getName() == patientName) {
                return p;
            }
        } else { // Case-insensitive search
            std::string pNameLower = p->getName();
            std::string searchNameLower = patientName;
            std::transform(pNameLower.begin(), pNameLower.end(), pNameLower.begin(), ::tolower);
            std::transform(searchNameLower.begin(), searchNameLower.end(), searchNameLower.begin(), ::tolower);
            if (pNameLower == searchNameLower) {
                return p;
            }
        }
    }
    return nullptr;
}

// Searches for a doctor by ID
std::shared_ptr<Doctor> Hospital::searchDoctor(int doctorID) const {
    for (const auto& d : doctors) {
        if (d->getDoctorID() == doctorID) {
            return d;
        }
    }
    return nullptr;
}

// Searches for a doctor by name, with case-sensitive option
std::shared_ptr<Doctor> Hospital::searchDoctor(const std::string& doctorName, bool caseSensitive) const {
    for (const auto& d : doctors) {
        if (caseSensitive) {
            if (d->getName() == doctorName) {
                return d;
            }
        } else { // Case-insensitive search
            std::string dNameLower = d->getName();
            std::string searchNameLower = doctorName;
            std::transform(dNameLower.begin(), dNameLower.end(), dNameLower.begin(), ::tolower);
            std::transform(searchNameLower.begin(), searchNameLower.end(), searchNameLower.begin(), ::tolower);
            if (dNameLower == searchNameLower) {
                return d;
            }
        }
    }
    return nullptr;
}

// Searches for an appointment by ID
std::shared_ptr<Appointment> Hospital::searchAppointment(int appointmentID) const {
    for (const auto& app : appointments) {
        if (app->getAppointmentID() == appointmentID) {
            return app; // Found appointment, return shared_ptr
        }
    }
    return nullptr; // Appointment not found
}

// Displays information for all registered patients
void Hospital::displayAllPatients() const {
    if (patients.empty()) {
        std::cout << "No patients registered." << std::endl;
        return;
    }
    std::cout << "\n--- All Patients ---" << std::endl;
    for (const auto& p : patients) {
        p->displayInfo(); // Call displayInfo for each patient
    }
    std::cout << "--------------------" << std::endl;
}

// Displays information for all registered doctors
void Hospital::displayAllDoctors() const {
    if (doctors.empty()) {
        std::cout << "No doctors registered." << std::endl;
        return;
    }
    std::cout << "\n--- All Doctors ---" << std::endl;
    for (const auto& d : doctors) {
        d->displayInfo(); // Call displayInfo for each doctor
    }
    std::cout << "-------------------" << std::endl;
}

// Displays information for all scheduled appointments
void Hospital::displayAllAppointments() const {
    if (appointments.empty()) {
        std::cout << "No appointments scheduled." << std::endl;
        return;
    }
    std::cout << "\n--- All Appointments ---" << std::endl;
    for (const auto& a : appointments) {
        a->displayInfo(); // Call displayInfo for each appointment
    }
    std::cout << "------------------------" << std::endl;
}