#ifndef HOSPITAL_SYSTEM_H
#define HOSPITAL_SYSTEM_H

#include <string>
#include <vector>
#include <memory> // For std::shared_ptr

// Forward declarations for classes that refer to each other
class Patient;
class Doctor;
class Appointment;

// --- Person Class (Base Class) ---
// Base class for all individuals in the system
class Person {
public:
    // Constructor
    explicit Person(const std::string& _name, int _age = 0, const std::string& _gender = "Unknown");
    // Virtual destructor for proper polymorphic cleanup
    virtual ~Person();

    // Setters
    void setName(const std::string& _name);
    void setAge(int _age);
    void setGender(const std::string& _gender);

    // Getters
    std::string getName() const;
    int getAge() const;
    std::string getGender() const;

    // Virtual function to display information (can be overridden by derived classes)
    virtual void displayInfo() const;

private:
    std::string name;
    int age;
    std::string gender;
};

// --- Patient Class (Derived from Person) ---
class Patient : public Person {
public:
    // Constructor
    explicit Patient(const std::string& _name, int _age, const std::string& _gender,
                     const std::string& _disease = "N/A", int _patientID = 0);
    // Destructor
    ~Patient();

    // Setters
    void setPatientID(int _patientID);
    void setDisease(const std::string& _disease);
    void addMedicalRecord(const std::string& record);
    void displayMedicalHistory() const;

    // Getters
    int getPatientID() const;
    std::string getDisease() const;
    const std::vector<std::string>& getMedicalHistory() const;

    // Override displayInfo from Person class
    void displayInfo() const override;

private:
    int patientID;
    std::string disease;
    std::vector<std::string> medicalHistory;
    static int nextPatientID; // Static member to generate unique patient IDs
};

// --- Doctor Class (Derived from Person) ---
class Doctor : public Person {
public:
    // Constructor
    explicit Doctor(const std::string& _name, int _age, const std::string& _gender,
                    const std::string& _specialization = "General", int _licenseNumber = 0);
    // Destructor
    ~Doctor();

    // Setters
    void setDoctorID(int _doctorID);
    void setSpecialization(const std::string& _specialization);
    void setLicenseNumber(int _licenseNumber);
    void updateSpecialization(const std::string& newSpecialization);

    // Getters
    int getDoctorID() const;
    std::string getSpecialization() const;
    int getLicenseNumber() const;

    // Override displayInfo from Person class
    void displayInfo() const override;

private:
    int doctorID;
    std::string specialization;
    int licenseNumber;
    static int nextDoctorID; // Static member to generate unique doctor IDs
};

// --- Appointment Class (Composition) ---
// Represents an appointment between a patient and a doctor
class Appointment {
public:
    // Constructor
    explicit Appointment(int _appointmentID, const std::string& _date, const std::string& _time,
                         std::shared_ptr<Patient> _patient, std::shared_ptr<Doctor> _doctor);
    // Destructor
    ~Appointment();

    // Setters
    void setAppointmentID(int _appointmentID);
    void setDate(const std::string& _date);
    void setTime(const std::string& _time);
    void setStatus(const std::string& _status);

    // Getters
    int getAppointmentID() const;
    std::string getDate() const;
    std::string getTime() const;
    std::string getStatus() const;
    std::shared_ptr<Patient> getPatient() const; // Returns a shared_ptr to the patient
    std::shared_ptr<Doctor> getDoctor() const;   // Returns a shared_ptr to the doctor

    // Function overloading for reschedule
    void reschedule(const std::string& newDate, const std::string& newTime); // Reschedule with both date and time
    void reschedule(const std::string& newDate); // Reschedule with date only (keep current time)

    // Specific function for rescheduling used in main
    void rescheduleAppointment(const std::string& newDate, const std::string& newTime);
    void displayInfo() const;

private:
    int appointmentID;
    std::string date;
    std::string time;
    std::string status;
    std::shared_ptr<Patient> patient; // Composition: Appointment 'has-a' Patient
    std::shared_ptr<Doctor> doctor;   // Composition: Appointment 'has-a' Doctor
    static int nextAppointmentID;     // Static member to generate unique appointment IDs
};

// --- Hospital Class (Main System) ---
// Manages collections of patients, doctors, and appointments
class Hospital {
public:
    // Methods to add entities to the hospital system
    void addPatient(std::shared_ptr<Patient> patient);
    void addDoctor(std::shared_ptr<Doctor> doctor);
    void addAppointment(std::shared_ptr<Appointment> appointment);

    // Methods to search for entities
    std::shared_ptr<Patient> searchPatient(int patientID) const;
    std::shared_ptr<Patient> searchPatient(const std::string& patientName, bool caseSensitive = false) const;
    std::shared_ptr<Appointment> searchAppointment(int appointmentID) const;
    std::shared_ptr<Doctor> searchDoctor(int doctorID) const;
    std::shared_ptr<Doctor> searchDoctor(const std::string& doctorName, bool caseSensitive = false) const;

    // Methods to display all entities
    void displayAllPatients() const;
    void displayAllDoctors() const;
    void displayAllAppointments() const;

private:
    // Vectors to store shared_ptr to managed objects, ensuring proper memory management
    std::vector<std::shared_ptr<Patient>> patients;
    std::vector<std::shared_ptr<Doctor>> doctors;
    std::vector<std::shared_ptr<Appointment>> appointments;
};

#endif // HOSPITAL_SYSTEM_H