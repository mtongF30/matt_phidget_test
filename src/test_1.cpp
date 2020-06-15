#include <ros/ros.h>
#include <stdio.h>
#include <math.h>


#include <phidgets_api/phidget.h>


int main(int argc, char** argv) {

 	ros::init(argc, argv, "test_1");
	ros::NodeHandle nh;



	// Create a handle for the connected phidget
		CPhidgetStepperHandle handle;

    // Create the stepper motor object
		int err;
		err = CPhidgetStepper_create (&(handle));
		std::cout << "CPhidgetStepper_create err: " << err << std::endl;

	// Open the Phidget board
		err = CPhidget_open((CPhidgetHandle)handle, -1);
		std::cout << "CPhidget_open err: " << err << std::endl;

	// Attche the board
		err = CPhidget_waitForAttachment((CPhidgetHandle)handle, 10000);
		std::cout << "CPhidget_waitForAttachment err: " << err << std::endl;

	// Test get fncs
		int serial;
		err = CPhidget_getSerialNumber((CPhidgetHandle)handle, &serial);
		std::cout << "serial: " << serial << std::endl;

	// Engage the stepper motor
		err = CPhidgetStepper_setEngaged(handle, 0, 1);
	

	// Get position max minb
		__int64 position_max;
		__int64 position_min;
		CPhidgetStepper_getPositionMax(handle, 0, & position_max);
		CPhidgetStepper_getPositionMin(handle, 0, & position_min);
		std::cout << "position_max: " << position_max << std::endl;
		std::cout << "position_min: " << position_min << std::endl;



	// Get velocity 
		double velocity;
		err = CPhidgetStepper_getVelocity(handle, 0, &velocity);
		std::cout << "velocity: " << velocity << std::endl;

		double v_limit;
		err = CPhidgetStepper_getVelocityLimit(handle, 0, &v_limit);
		std::cout << "v_limit: " << v_limit << std::endl;

		v_limit = 700;
		CPhidgetStepper_setVelocityLimit(handle, 0, v_limit);

	// Set current location
		// __int64 current_loc = 0; 
		// CPhidgetStepper_setCurrentPosition(handle, 0, current_loc);


	// Set Acceleration 
		double acceleration = 100;
		CPhidgetStepper_setAcceleration(handle, 0, acceleration);


	// Test set target position 
		CPhidgetStepper_setTargetPosition(handle, 0, 0);
	 	ros::Duration(2).sleep();
		CPhidgetStepper_setTargetPosition(handle, 0, -700);
		 ros::Duration(5).sleep();
		//CPhidgetStepper_setTargetPosition(handle, 0, 0);
		// ros::Duration(7).sleep();
		//CPhidgetStepper_setTargetPosition(handle, 0, 650);
	 	//ros::Duration(5).sleep();
		CPhidgetStepper_setTargetPosition(handle, 0, 0);

		err = CPhidgetStepper_getVelocity(handle, 0, &velocity);
		//std::cout << "velocity: " << velocity << std::endl;

		__int64 current_loc;
		while (ros::ok()) {

			CPhidgetStepper_getCurrentPosition (handle, 0, &current_loc);
			//std::cout << "current_loc: " << current_loc << std::endl;

	}

	// Stop the stepper motor
	err = CPhidgetStepper_setEngaged(handle, 0, 0);

}