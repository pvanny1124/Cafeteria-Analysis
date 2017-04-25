// Provided by:   Patrick Vanegas - EMPL ID: 15172605
// Email Address: vanegas.patrick@yahoo.com

// project3 - Cafeteria Simulation
//
//	FILE: cafeteria.cpp
//	PROVIDES: implementations for the cafeteria class
#include <string>
#include <stack>
#include <queue>
#include <fstream> //provides ifstream
#include "cafeteria.h"
#include <iostream>
#include <vector>
#include <iomanip> //provides setprecision
#include <cstdlib> //provides rand
using namespace std;


namespace csc212_kl_f2012_a4template
{

	void Cafeteria::genTray(size_t numPerColor)
	{
		//Generates the trays and randomly splits them into two stacks
		// the number 1 is denoted to be red
		// the number 2 is denoted to be blue
		// the number 3 is denoted to be green
		srand(seed);	//sets the seed
		int redTrays(numPerColor), blueTrays(numPerColor), greenTrays(numPerColor);
		
		//empty the two stacks 
		for (size_t i=0; i < ts1.size(); i++)
			ts1.pop();
		
		for (size_t i=0; i < ts2.size(); i++)
			ts2.pop();
		
		while((redTrays!= 0) || (blueTrays!=0) || (greenTrays!=0)) //while there are still trays
		{
			int colorNum = rand()%3 + 1; //generates rand num between 1 and 3
			int stackNum = rand()%2 + 1; //generates rand num between 1 and 2
			
			//detetrmines the rand color and pushes it into the random stack
			switch(colorNum){
			case 1: //red case
				if((stackNum == 1) && (redTrays > 0) )
				{
					ts1.push(Tray(redTrays,"red"));
					redTrays--;

				}
				else if ((stackNum == 2) && (redTrays > 0) )
				{
					ts2.push(Tray(redTrays,"red"));
					redTrays--;
				}
				break;
			case 2: //blue case
				if((stackNum == 1) && (blueTrays > 0) )
				{
					ts1.push(Tray(blueTrays,"blue"));
					blueTrays--;
				}
				else if ((stackNum == 2) && (blueTrays > 0) )
				{
					ts2.push(Tray(blueTrays,"blue"));
					blueTrays--;
				}
				break;
			case 3: //green case
				if((stackNum == 1) && (greenTrays > 0) )
				{
					ts1.push(Tray(greenTrays,"green"));
					greenTrays--;
				}
				else if ((stackNum == 2) && (greenTrays > 0) )
				{
					ts2.push(Tray(greenTrays,"green"));
					greenTrays--;
				}
				break;
			}
		}
 //TESTING 
		/*
		cout << "\nDISPLAYING STACK 1" << endl;
		int trayCount(0);
		stack<Tray> temps1(ts1), temps2(ts2); 
		while(!temps1.empty())
		{
			trayCount++;
			Tray temp = temps1.top();
			temps1.pop();
			cout << "Tray Number: " << trayCount << " Color: " << temp.getColor() << " ID: " << temp.getID() << endl;
		}
		cout << "\nDISPLAYING STACK 2" << endl;
		while(!temps2.empty())
		{
			trayCount++;
			Tray temp = temps2.top();
			temps2.pop();

			cout << "Tray Number: " << trayCount<< " Color: " << temp.getColor() << " ID: " << temp.getID() << endl;
		} 
		cout << endl; */
		
	} 

	void Cafeteria::pickTray()
	{
		Group redg("red"), greeng("green"), blueg("blue");
		size_t count = ts1.size() + ts2.size(); //size of both stacks combined
		srand(seed);
		//STUDENT-TRAY SELECTION
		while (!student_queue.empty())
		{
			
			int random_tray = rand() % 2 + 1; //used for picking a random tray #1 or #2
			switch (random_tray)
			{
			case 1:
				if (random_tray == 1)
				{
				Tray temp_tray1 = ts1.top(); //temp for top tray of ts1
				/*if no tray is found after while loop, proceeds to case 2*/
				/*else proceeds to case 1*/
				while (temp_tray1.getColor() != student_queue.front().getGroup())
				{
					if (ts1.empty())
						break;
					Tray temp = ts1.top();
					ts1.pop();
					ts2.push(temp);
					temp_tray1 = ts1.top(); //continue looping
				}
				/*case 1*/
				if (temp_tray1.getColor() == student_queue.front().getGroup())
				{
					
					//following ensure next_stu goes into right group without using switch statements
					redg.addStudent(student_queue.front());
					greeng.addStudent(student_queue.front());
					blueg.addStudent(student_queue.front());
					student_queue.pop(); //removes the student from the list
					ts1.pop(); //pops the tray out of the collection
					count--;
					break;
				}
				/*case 2*/
				/*If all trays have been stacked on ts2, now check ts2...*/
				else if (ts2.size() == count)
				{
					Tray temp_tray2 = ts2.top(); //holds temp of top of stack ts2
					/*repeats processes; if no tray is absolutely found, choose top of stack 1*/
					while (temp_tray2.getColor() != student_queue.front().getGroup())
					{
						Tray temp2 = ts2.top();
						ts2.pop();
						ts1.push(temp2);
					if (ts2.empty())
							break;
						temp_tray2 = ts2.top();
					}
					if (temp_tray2.getColor() == student_queue.front().getGroup())
					{
						
						redg.addStudent(student_queue.front());
						greeng.addStudent(student_queue.front());
						blueg.addStudent(student_queue.front());
						student_queue.pop();
						ts2.pop();
						count--;
						break;
					}
					
					/*if no tray was found, pick the top tray of stack 1...*/
					if (ts1.size() == count && ts2.empty())
					{
						
						redg.addStudent(student_queue.front());
						greeng.addStudent(student_queue.front());
						blueg.addStudent(student_queue.front());
						student_queue.pop();
						ts1.pop();
						count--;
						break;

					}
				}
			}
			case 2:
				if (random_tray == 2)
				{
					/*same procedure as case 1, now start looking through stack 2*/
					Tray temp_tray2 = ts2.top(); //temp for top tray of ts2
					/*if no tray is found after while loop, proceeds to case 2*/
					/*else proceeds to case 1*/
					while (temp_tray2.getColor() != student_queue.front().getGroup())
					{
						if (ts2.empty())
							break;
						Tray temp = ts2.top();
						ts2.pop();
						ts1.push(temp);
						temp_tray2 = ts2.top(); //continue looping
					}

					/*case 1*/
					if (temp_tray2.getColor() == student_queue.front().getGroup())
					{
						
						//following ensure next_stu goes into right group without using switch statements
						redg.addStudent(student_queue.front());
						greeng.addStudent(student_queue.front());
						blueg.addStudent(student_queue.front());
						student_queue.pop(); //removes the student from the list
						ts2.pop(); //pops the tray out of the collection
						count--;
						break;
					}
					/*case 2*/
					/*If all trays have been stacked on ts1, now check ts1...*/
					else if (ts1.size() == count)
					{
						Tray temp_tray1 = ts1.top(); //holds temp of top of stack ts1
						/*repeats processes; if no tray is absolutely found, choose top of stack 2*/
						while (temp_tray1.getColor() != student_queue.front().getGroup())
						{
							if (ts1.empty())
								break;
							Tray temp2 = ts1.top();
							ts1.pop();
							ts2.push(temp2);
							temp_tray1 = ts1.top();
						}
						if (temp_tray1.getColor() == student_queue.front().getGroup())
						{
							
							redg.addStudent(student_queue.front());
							greeng.addStudent(student_queue.front());
							blueg.addStudent(student_queue.front());
							student_queue.pop();
							ts1.pop();
							count--;
							break;

						}
						/*if no tray was found, pick the top tray of stack 2...*/
						if (ts2.size() == count && ts1.empty())
						{
							
							redg.addStudent(student_queue.front());
							greeng.addStudent(student_queue.front());
							blueg.addStudent(student_queue.front());
							student_queue.pop();
							ts2.pop();
							count--;
							break;

						}


					}



				}
			} 
		}
			/*insert all groups (with students inside) to groups vector*/
			groups.push_back(redg);
			groups.push_back(greeng);
			groups.push_back(blueg);
						
		}

	
	
		
		/*
		YOUR CODE GOES HERE
		for each student in the queue
			1 pick a tray 
				1.1 randomly select a stack (as #1 tray)
				1.2 pop #1 stack and push #2 stack until find the desired color
				1.3 if no tray is found, pop #2 stack and push #1 stack and continue to find the tray of desired color
				1.4: if no tray is found, pick the top one of #1 stack. 
			2. identify the color of the picked tray
			3. push the student into the queue/stack of the corresponding group 
		*/		
	
	void Cafeteria::printGroup()
	{
		//prints each group
		for(size_t i=0; i<groups.size(); i++)
		{
			cout << groups[i] << endl;;
		}
	}

}