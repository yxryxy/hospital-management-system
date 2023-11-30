all: main.cpp ./src/global.cpp ./src/hospital.cpp ./src/address.cpp ./src/person.cpp ./src/doctor.cpp ./src/patient.cpp ./src/appointment.cpp ./src/nurse.cpp ./src/driver.cpp ./src/ambulance.cpp ./src/pharmacy.cpp ./src/ward.cpp ./src/finance.cpp
	g++ -o "./build/hms" main.cpp ./src/global.cpp ./src/hospital.cpp ./src/address.cpp ./src/person.cpp ./src/doctor.cpp ./src/patient.cpp ./src/appointment.cpp ./src/nurse.cpp ./src/driver.cpp ./src/ambulance.cpp ./src/pharmacy.cpp ./src/ward.cpp ./src/finance.cpp

run:
	./build/hms

clean:
	rm -f ./build/*

clean(win):
	del /f build\*

headers: ./include/address.hh ./include/ambulance.hh ./include/appointment.hh ./include/doctor.hh ./include/driver.hh ./include/global.hh ./include/hospital.hh ./include/nurse.hh ./include/patient.hh ./include/person.hh ./include/pharmacy.hh ./include/ward.hh ./include/finance.hh
	g++ ./include/address.hh ./include/ambulance.hh ./include/appointment.hh ./include/doctor.hh ./include/driver.hh ./include/global.hh ./include/hospital.hh ./include/nurse.hh ./include/patient.hh ./include/person.hh ./include/pharmacy.hh ./include/ward.hh ./include/finance.hh