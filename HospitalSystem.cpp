#include <iostream>
#include <stdexcept>
#include <algorithm> // For std::transform
#include <cctype>    // For ::tolower
#include <memory>    // For std::shared_ptr

#include "HospitalSystem.h" // Include the combined header

// --- Person Class Implementation ---
Person::Person(const std::string& _name, int _age, const std::string& _gender) {
    setName(_name);
    setAge(_age);
    setGender(_gender);
}

Person::~Person() {
    // std::cout << "Person " << name << " destroyed." << std::endl;
}

void Person::setName(const std::string& _name) {
    if (_name.empty()) {
        throw std::invalid_argument("Name cannot be empty!");
    }
    name = _name;
}

void Person::setAge(int _age) {
    if (_age < 0 || _age > 120) {
        throw std::invalid_argument("Invalid age!");
    }
    age = _age;
}

void Person::setGender(const std::string& _gender) {
    if (_gender != "Male" && _gender != "Female" && _gender != "Unknown") {
        std::cout << "Warning: Invalid gender specified. Setting to 'Unknown'." << std::endl;
        gender = "Unknown";
    } else {
        gender = _gender;
    }
}

std::string Person::getName() const {
    return name;
}

int Person::getAge() const {
    return age;
}

std::string Person::getGender() const {
    return gender;
}

void Person::displayInfo() const {
    std::cout << "Name: " << name << ", Age: " << age << ", Gender: " << gender;
}

// --- Patient Class Implementation ---
// Initialize static member
int Patient::nextPatientID = 1001; // Starting patient IDs from 1001

Patient::Patient(const std::string& _name, int _age, const std::string& _gender,
                 const std::string& _disease, int _patientID)
    : Person(_name, _age, _gender) {
    if (_patientID == 0) {
        setPatientID(nextPatientID++);
    } else {
        setPatientID(_patientID);
    }
    setDisease(_disease);
}

Patient::~Patient() {
    // std::cout << "Patient " << getName() << " destroyed." << std::endl;
}

void Patient::setPatientID(int _patientID) {
    if (_patientID <= 0) {
        throw std::invalid_argument("Patient ID must be positive!");
    }
    patientID = _patientID;
}

void Patient::setDisease(const std::string& _disease) {
    disease = _disease;
}

void Patient::addMedicalRecord(const std::string& record) {
    if (record.empty()) {
        throw std::invalid_argument("Medical record cannot be empty!");
    }
    medicalHistory.push_back(record);
    std::cout << "Medical record added for patient " << getName() << "." << std::endl;
}

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

int Patient::getPatientID() const {
    return patientID;
}

std::string Patient::getDisease() const {
    return disease;
}

const std::vector<std::string>& Patient::getMedicalHistory() const {
    return medicalHistory;
}

void Patient::displayInfo() const {
    Person::displayInfo();
    std::cout << ", Patient ID: " << patientID << ", Disease: " << disease << std::endl;
}

// --- Doctor Class Implementation ---
// Initialize static member
int Doctor::nextDoctorID = 2001; // Starting doctor IDs from 2001

Doctor::Doctor(const std::string& _name, int _age, const std::string& _gender,
               const std::string& _specialization, int _licenseNumber)
    : Person(_name, _age, _gender) {
    setDoctorID(nextDoctorID++);
    setSpecialization(_specialization);
    setLicenseNumber(_licenseNumber);
}

Doctor::~Doctor() {
    // std::cout << "Doctor " << getName() << " destroyed." << std::endl;
}

void Doctor::setDoctorID(int _doctorID) {
    if (_doctorID <= 0) {
        throw std::invalid_argument("Doctor ID must be positive!");
    }
    doctorID = _doctorID;
}

void Doctor::setSpecialization(const std::string& _specialization) {
    if (_specialization.empty()) {
        throw std::invalid_argument("Specialization cannot be empty!");
    }
    specialization = _specialization;
}

void Doctor::setLicenseNumber(int _licenseNumber) {
    if (_licenseNumber <= 0) {
        std::cout << "Warning: Invalid license number. Setting to 0." << std::endl;
        licenseNumber = 0;
    } else {
        licenseNumber = _licenseNumber;
    }
}

void Doctor::updateSpecialization(const std::string& newSpecialization) {
    setSpecialization(newSpecialization);
    std::cout << "Doctor " << getName() << "'s specialization updated to " << newSpecialization << "." << std::endl;
}

int Doctor::getDoctorID() const {
    return doctorID;
}

std::string Doctor::getSpecialization() const {
    return specialization;
}

int Doctor::getLicenseNumber() const {
    return licenseNumber;
}

void Doctor::displayInfo() const {
    Person::displayInfo();
    std::cout << ", Doctor ID: " << doctorID << ", Specialization: " << specialization
              << ", License: " << licenseNumber << std::endl;
}

// --- Appointment Class Implementation ---
// Initialize static member
int Appointment::nextAppointmentID = 3001; // Starting appointment IDs from 3001

Appointment::Appointment(int _appointmentID, const std::string& _date, const std::string& _time,
                         std::shared_ptr<Patient> _patient, std::shared_ptr<Doctor> _doctor) {
    if (_appointmentID == 0) {
        setAppointmentID(nextAppointmentID++);
    } else {
        setAppointmentID(_appointmentID);
    }
    setDate(_date);
    setTime(_time);
    patient = _patient;
    doctor = _doctor;
    setStatus("Booked");
}

Appointment::~Appointment() {
    // std::cout << "Appointment " << appointmentID << " destroyed." << std::endl;
}

void Appointment::setAppointmentID(int _appointmentID) {
    if (_appointmentID <= 0) {
        throw std::invalid_argument("Appointment ID must be positive!");
    }
    appointmentID = _appointmentID;
}

void Appointment::setDate(const std::string& _date) {
    if (_date.empty()) {
        throw std::invalid_argument("Date cannot be empty!");
    }
    date = _date;
}

void Appointment::setTime(const std::string& _time) {
    if (_time.empty()) {
        throw std::invalid_argument("Time cannot be empty!");
    }
    time = _time;
}

void Appointment::setStatus(const std::string& _status) {
    status = _status;
}

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

std::shared_ptr<Patient> Appointment::getPatient() const {
    return patient;
}

std::shared_ptr<Doctor> Appointment::getDoctor() const {
    return doctor;
}

// THIS IS THE NEW rescheduleAppointment FUNCTION
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

// If you still want the overloaded 'reschedule' function (single argument) you had before, keep it.
// But the one used in main.cpp will be rescheduleAppointment.
// You might want to rename the one below to 'rescheduleDateOnly' or remove it to avoid confusion.
// For now, I'm keeping your original 'reschedule' functions as you provided them in your code.
void Appointment::reschedule(const std::string& newDate, const std::string& newTime) {
    if (newDate.empty() || newTime.empty()) { // Both date and time must be provided now
        throw std::invalid_argument("New date and time for reschedule cannot be empty!");
    }
    setDate(newDate);
    setTime(newTime);
    setStatus("Rescheduled");
    std::cout << "Appointment " << appointmentID << " rescheduled to " << date
              << " at " << time << "." << std::endl;
}

// Function overloading (one argument - date only)
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
// ... (Your existing Appointment code) ...

void Appointment::displayInfo() const {
    std::cout << "Appointment ID: " << appointmentID
              << ", Date: " << date << ", Time: " << time
              << ", Status: " << status << std::endl;
    if (patient) {
        std::cout << "  Patient: " << patient->getName() << " (ID: " << patient->getPatientID() << ")";
    }
    if (doctor) {
        std::cout << ", Doctor: " << doctor->getName() << " (Specialization: " << doctor->getSpecialization() << ")";
    }
    std::cout << std::endl;
}

// --- Hospital Class Implementation ---
void Hospital::addPatient(std::shared_ptr<Patient> patient) {
    patients.push_back(patient);
    std::cout << "Patient " << patient->getName() << " added." << std::endl;
}

void Hospital::addDoctor(std::shared_ptr<Doctor> doctor) {
    doctors.push_back(doctor);
    std::cout << "Doctor " << doctor->getName() << " added." << std::endl;
}

void Hospital::addAppointment(std::shared_ptr<Appointment> appointment) {
    appointments.push_back(appointment);
    std::cout << "Appointment " << appointment->getAppointmentID() << " added." << std::endl;
}

std::shared_ptr<Patient> Hospital::searchPatient(int patientID) const {
    for (const auto& p : patients) {
        if (p->getPatientID() == patientID) {
            return p;
        }
    }
    return nullptr;
}

std::shared_ptr<Patient> Hospital::searchPatient(const std::string& patientName, bool caseSensitive) const {
    for (const auto& p : patients) {
        if (caseSensitive) {
            if (p->getName() == patientName) {
                return p;
            }
        } else {
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

std::shared_ptr<Doctor> Hospital::searchDoctor(int doctorID) const {
    for (const auto& d : doctors) {
        if (d->getDoctorID() == doctorID) {
            return d;
        }
    }
    return nullptr;
}

std::shared_ptr<Doctor> Hospital::searchDoctor(const std::string& doctorName, bool caseSensitive) const {
    for (const auto& d : doctors) {
        if (caseSensitive) {
            if (d->getName() == doctorName) {
                return d;
            }
        } else {
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

// THIS IS THE NEW Hospital::searchAppointment FUNCTION
std::shared_ptr<Appointment> Hospital::searchAppointment(int appointmentID) const {
    for (const auto& app : appointments) { // 'appointments' هو vector المواعيد في كلاس Hospital
        if (app->getAppointmentID() == appointmentID) {
            return app; // أوجدنا الموعد، نرجعه
        }
    }
    return nullptr; // لم يتم العثور على الموعد
}

void Hospital::displayAllPatients() const {
    if (patients.empty()) {
        std::cout << "No patients registered." << std::endl;
        return;
    }
    std::cout << "\n--- All Patients ---" << std::endl;
    for (const auto& p : patients) {
        p->displayInfo();
    }
    std::cout << "--------------------" << std::endl;
}

void Hospital::displayAllDoctors() const {
    if (doctors.empty()) {
        std::cout << "No doctors registered." << std::endl;
        return;
    }
    std::cout << "\n--- All Doctors ---" << std::endl;
    for (const auto& d : doctors) {
        d->displayInfo();
    }
    std::cout << "-------------------" << std::endl;
}

void Hospital::displayAllAppointments() const {
    if (appointments.empty()) {
        std::cout << "No appointments scheduled." << std::endl;
        return;
    }
    std::cout << "\n--- All Appointments ---" << std::endl;
    for (const auto& a : appointments) {
        a->displayInfo();
    }
    std::cout << "------------------------" << std::endl;
}