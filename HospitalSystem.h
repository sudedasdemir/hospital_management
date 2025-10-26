#ifndef HOSPITAL_SYSTEM_H
#define HOSPITAL_SYSTEM_H

#include <string>
#include <vector>
#include <memory> // For std::shared_ptr

// Forward declarations for classes that refer to each other
class Patient;
class Doctor;
class Appointment;
class Hospital; // If Hospital class uses these in its header, otherwise not strictly needed here

// --- Person Class (Base Class) ---
class Person {
public:
    explicit Person(const std::string& _name, int _age = 0, const std::string& _gender = "Unknown");
    virtual ~Person();

    void setName(const std::string& _name);
    void setAge(int _age);
    void setGender(const std::string& _gender);

    std::string getName() const;
    int getAge() const;
    std::string getGender() const;

    virtual void displayInfo() const;

private:
    std::string name;
    int age;
    std::string gender;
};

// --- Patient Class (Derived from Person) ---
class Patient : public Person {
public:
    explicit Patient(const std::string& _name, int _age, const std::string& _gender,
                     const std::string& _disease = "N/A", int _patientID = 0);
    ~Patient();

    void setPatientID(int _patientID);
    void setDisease(const std::string& _disease);
    void addMedicalRecord(const std::string& record);
    void displayMedicalHistory() const;

    int getPatientID() const;
    std::string getDisease() const;
    const std::vector<std::string>& getMedicalHistory() const;

    void displayInfo() const override;

private:
    int patientID;
    std::string disease;
    std::vector<std::string> medicalHistory;
    static int nextPatientID; // Static member declaration
};

// --- Doctor Class (Derived from Person) ---
class Doctor : public Person {
public:
    explicit Doctor(const std::string& _name, int _age, const std::string& _gender,
                    const std::string& _specialization = "General", int _licenseNumber = 0);
    ~Doctor();

    void setDoctorID(int _doctorID);
    void setSpecialization(const std::string& _specialization);
    void setLicenseNumber(int _licenseNumber);
    void updateSpecialization(const std::string& newSpecialization);

    int getDoctorID() const;
    std::string getSpecialization() const;
    int getLicenseNumber() const;

    void displayInfo() const override;

private:
    int doctorID;
    std::string specialization;
    int licenseNumber;
    static int nextDoctorID; // Static member declaration
};

// --- Appointment Class (Composition) ---
class Appointment {
public:
    explicit Appointment(int _appointmentID, const std::string& _date, const std::string& _time,
                         std::shared_ptr<Patient> _patient, std::shared_ptr<Doctor> _doctor);
    ~Appointment();

    void setAppointmentID(int _appointmentID);
    void setDate(const std::string& _date);
    void setTime(const std::string& _time);
    void setStatus(const std::string& _status);

    int getAppointmentID() const;
    std::string getDate() const;
    std::string getTime() const;
    std::string getStatus() const;
    std::shared_ptr<Patient> getPatient() const;
    std::shared_ptr<Doctor> getDoctor() const;

    // Function overloading for reschedule
    void reschedule(const std::string& newDate, const std::string& newTime); // No default argument here
    void reschedule(const std::string& newDate); // Overload without new time

    void rescheduleAppointment(const std::string& newDate, const std::string& newTime);
    void displayInfo() const;

private:
    int appointmentID;
    std::string date;
    std::string time;
    std::string status;
    std::shared_ptr<Patient> patient;
    std::shared_ptr<Doctor> doctor;
    static int nextAppointmentID; // Static member declaration
};

// --- Hospital Class (Main System) ---
class Hospital {
public:
    void addPatient(std::shared_ptr<Patient> patient);
    void addDoctor(std::shared_ptr<Doctor> doctor);
    void addAppointment(std::shared_ptr<Appointment> appointment);

    std::shared_ptr<Patient> searchPatient(int patientID) const;
    std::shared_ptr<Patient> searchPatient(const std::string& patientName, bool caseSensitive = false) const;

    std::shared_ptr<Appointment> searchAppointment(int appointmentID) const;
    std::shared_ptr<Doctor> searchDoctor(int doctorID) const; // Added for completeness
    std::shared_ptr<Doctor> searchDoctor(const std::string& doctorName, bool caseSensitive = false) const; // Added for completeness

    void displayAllPatients() const;
    void displayAllDoctors() const;
    void displayAllAppointments() const;

private:
    std::vector<std::shared_ptr<Patient>> patients;
    std::vector<std::shared_ptr<Doctor>> doctors;
    std::vector<std::shared_ptr<Appointment>> appointments;
};

#endif // HOSPITAL_SYSTEM_H