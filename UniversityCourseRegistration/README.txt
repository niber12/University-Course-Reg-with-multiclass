UNIVERSITY COURSE REGISTRATION SYSTEM

This project follows the OOP II Project Structure guide:
- include/: class declarations (.h)
- src/: class definitions (.cpp) and main.cpp
- FileManager.h / FileManager.cpp: the only class that reads and writes TXT files
- Admin can add students with an ID, name, major, and initial password.
- Admin can remove students, their login accounts, and their course registrations.
- Makefile: builds all source files

Student login accounts:
20253623  password 1234  (Hossain Md Niber)
20253633  password 2345  (Ahmed Md Miraj)
20253657  password 3456  (Gautam Dilip)
20253638  password 4567  (Thapa Rabin)

Admin login:
A1001  password admin123

Run on Windows with MinGW:
1. Open this folder in VS Code.
2. Terminal > New Terminal.
3. Run: mingw32-make
4. Run: .\app.exe

Alternative without Make:
g++ src/main.cpp src/User.cpp src/Student.cpp src/Admin.cpp src/Course.cpp src/Registration.cpp src/FileManager.cpp src/AuthSystem.cpp src/InputHelper.cpp src/RegistrationException.cpp src/UniversitySystem.cpp src/Menu.cpp -Iinclude -o app.exe
Then run: .\app.exe

The passwords are simple demonstration passwords for a classroom project.

Admin can add a student:
- Log in as admin and choose option 6 (Add Student).
- Enter the new student ID, full name, department/major, and initial password.
- Confirm the password. The student profile is saved in student_profiles.txt
  and the login ID/password are saved in students.txt.
- The new student can log in immediately and remains in the system after restart.
Course, registration, student login, and student profile information is saved in
courses.txt, registrations.txt, students.txt, and student_profiles.txt.
FileManager controls all four files. UniversitySystem handles registration rules and
asks FileManager to load or save data. Menu and main do not open TXT files.

TXT formats:
student_profiles.txt: studentId|fullName|major
courses.txt: courseId|title|credits|capacity
registrations.txt: studentId|courseId
students.txt: studentId|password

On the first run, the program uses its built-in default courses. After an admin
adds, updates, or deletes a course, courses.txt is created/updated automatically.
After a student registers or drops a course, registrations.txt is updated.

Student password change:
- After logging in, choose option 5 (Change Password) in the student menu.
- Enter the current password, a new password (at least 4 characters), and confirm it.
- The new password is saved in students.txt and remains changed after restarting the program.
- The admin password is unchanged.

Admin can remove a student:
- Log in as admin and choose option 7 (Remove Student).
- Select the student ID from the displayed student list.
- Confirm with y to remove the student.
- The student profile, login/password record, and all course registrations for that ID are deleted from their TXT files.
- Choose n to cancel.

Admin can remove a student:
- Log in as admin and choose option 7 (Remove Student).
- View the student list and enter the ID of the student to remove.
- Confirm with y to remove the student, or n to cancel.
- The student's login/password record, profile, and all course registrations are removed.
- The removal is saved in students.txt, student_profiles.txt, and registrations.txt.
- An intentionally empty student file stays empty after restarting; removed default accounts are not recreated.
