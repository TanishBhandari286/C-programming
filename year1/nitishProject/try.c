#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PATIENT_FILE "patients.dat"
#define DOCTOR_FILE "doctors.dat"
#define APPOINTMENT_FILE "appointments.dat"

struct Patient {
  int id;
  char name[50];
  int age;
  char contact[15];
  char medicalHistory[500];
};

struct Doctor {
  int id;
  char name[50];
  char specialization[30];
  char contact[15];
};

struct Appointment {
  int patientId;
  int doctorId;
  char date[11];
  char time[6];
};

void registerPatient();
void registerDoctor();
void scheduleAppointment();
void viewPatientHistory();
void menu();

int main() {
  menu();
  return 0;
}

void menu() {
  int choice;
  while (1) {
    printf("\n Hospital Management System\n");
    printf("1. Register Patient\n");
    printf("2. Register Doctor\n");
    printf("3. Schedule Appointment\n");
    printf("4. View Patient History\n");
    printf("5. Exit\n");
    printf("Choose an option: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
      registerPatient();
      break;
    case 2:
      registerDoctor();
      break;
    case 3:
      scheduleAppointment();
      break;
    case 4:
      viewPatientHistory();
      break;
    case 5:
      printf("Exiting...\n");
      exit(0);
    default:
      printf("Invalid choice, please try again.\n");
    }
  }
}

void registerPatient() {
  struct Patient newPatient;
  FILE *file = fopen(PATIENT_FILE, "ab");

  printf("Enter Patient ID: ");
  scanf("%d", &newPatient.id);
  printf("Enter Name: ");
  scanf(" %[^\n]", newPatient.name);
  printf("Enter Age: ");
  scanf("%d", &newPatient.age);
  printf("Enter Contact: ");
  scanf(" %[^\n]", newPatient.contact);
  printf("Enter Medical History: ");
  scanf(" %[^\n]", newPatient.medicalHistory);

  fwrite(&newPatient, sizeof(struct Patient), 1, file);
  fclose(file);

  printf("Patient registered successfully.\n");
}

void registerDoctor() {
  struct Doctor newDoctor;
  FILE *file = fopen(DOCTOR_FILE, "ab");

  printf("Enter Doctor ID: ");
  scanf("%d", &newDoctor.id);
  printf("Enter Name: ");
  scanf(" %[^\n]", newDoctor.name);
  printf("Enter Specialization: ");
  scanf(" %[^\n]", newDoctor.specialization);
  printf("Enter Contact: ");
  scanf(" %[^\n]", newDoctor.contact);

  fwrite(&newDoctor, sizeof(struct Doctor), 1, file);
  fclose(file);

  printf("Doctor registered successfully.\n");
}

void scheduleAppointment() {
  struct Appointment newAppointment;
  FILE *file = fopen(APPOINTMENT_FILE, "ab");

  printf("Enter Patient ID: ");
  scanf("%d", &newAppointment.patientId);
  printf("Enter Doctor ID: ");
  scanf("%d", &newAppointment.doctorId);
  printf("Enter Date (YYYY-MM-DD): ");
  scanf(" %[^\n]", newAppointment.date);
  printf("Enter Time (HH:MM): ");
  scanf(" %[^\n]", newAppointment.time);

  fwrite(&newAppointment, sizeof(struct Appointment), 1, file);
  fclose(file);

  printf("Appointment scheduled successfully.\n");
}

void viewPatientHistory() {
  int patientId, found = 0;
  struct Appointment appointment;
  FILE *file = fopen(APPOINTMENT_FILE, "rb");

  printf("Enter Patient ID to view history: ");
  scanf("%d", &patientId);

  printf("\n--- Medical History for Patient ID %d ---\n", patientId);
  while (fread(&appointment, sizeof(struct Appointment), 1, file)) {
    if (appointment.patientId == patientId) {
      printf("Doctor ID: %d\n", appointment.doctorId);
      printf("Date: %s\n", appointment.date);
      printf("Time: %s\n\n", appointment.time);
      found = 1;
    }
  }
  fclose(file);

  if (!found) {
    printf("No appointments found for Patient ID %d.\n", patientId);
  }
}
