// Baby Block Robot 04/09/19
// Matthew Hise, Issac Gann, and Chris Trahan
// Test Case Results Generating Version

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

char get_block(void);
unsigned int put_block(char block, unsigned int position, char array[]);
unsigned int calc_right_bound(char robot, unsigned int position, char array[]);
unsigned int shift_right(unsigned int position);
unsigned int shift_left(unsigned int position);
unsigned int shuffle_to(unsigned int position, unsigned int target);
bool robot_ltoreq_slot(char robot, char in_slot);
bool robot_eq_slot(char robot, char in_slot);
bool min_switch(unsigned int left_bound, unsigned int right_bound, char array[]);
unsigned int insert_block(unsigned int left_bound, char block, char array[]);
char switch_blocks(char robot, unsigned int position, char array[]);
bool test_empty(unsigned int position, char array[]);
void print_slots(char array_in[]);
unsigned int remove_block(unsigned int position, char array[]);

// Functions for the five test cases

char get_block_testcase(unsigned int testcase, unsigned int index);
char get_block_testone(void);
char get_block_testtwo(void);
char get_block_testthree(void);
char get_block_testfour(void);
char get_block_testfive(void);

unsigned int swap_count = 0;

int main(void)
{
	unsigned int position = 1, blocks_placed = 0;
	int k = 19;
	char current_block = ' ', temp = ' ';
	char slots[20] = { NULL };

	cout << "Welcome to the baby block robot! This robot will accurately and efficiently sort "
		 << "20 random letters A-Z one at a time. " << endl << endl;

	

	for (unsigned int tcase = 1; tcase <= 5; tcase++) {
		cout << "Running test case " << tcase << endl;
		do {
			cout << "Please enter the starting slot as a number from 1 to 20:" << endl;
			cin >> position; // Get start slot
		} while (position < 1 || position > 20);
		position--; // Decrement the position to account for the index starting at zero
		cout << "Excellent! The robot will begin at slot " << (position + 1) << endl << endl;
		
		while (blocks_placed < 20) {
			if (current_block == ' ')
				current_block = get_block_testcase(tcase, blocks_placed); // Get a block if the robot isn't currently holding one
			if (test_empty(position, slots)) {
				put_block(current_block, position, slots); // Place the block in the current slot if the slot is empty
				print_slots(slots);
				current_block = ' '; // Since the robot no longer has a block, set it to a blank
				blocks_placed++; // Increment the placed blocks counter
			}
			else { // If the current slot contains a block, compare it to the robot's block
				if (robot_ltoreq_slot(current_block, slots[position])) {
					if (position > 0) {
						position = shift_left(position); // Shift left one space if the robot can
					}
					else {
						position = insert_block(0, current_block, slots); // Insert the block if at the first slot
						print_slots(slots);
						current_block = ' ';
						blocks_placed++;
					}
				}
				else {
					if (position < 19) {
						position = shift_right(position);
						if (test_empty(position, slots)) { // If the slot to the right is empty, place the block there
							put_block(current_block, position, slots);
							print_slots(slots);
							current_block = ' ';
							blocks_placed++;
						}
						else { // Otherwise, see if the slot to the left is where the block should go
							if (robot_ltoreq_slot(current_block, slots[position])) {
								position = shift_left(position);
								position = insert_block(position, current_block, slots);
								print_slots(slots);
								current_block = ' ';
								blocks_placed++;
							}
							// Go back to top of loop with block if target slot is not found yet
						}
					}
					else { // Insert the block if at the last slot
						position = insert_block(19, current_block, slots);
						print_slots(slots);
						current_block = ' ';
						blocks_placed++;
					}
				}
			}
		}
		cout << swap_count << " swaps were required in this sorting." << endl << endl;
		swap_count = 0;
		blocks_placed = 0;
		position = 1;
		for (int i = 0; i < 20; i++) {
			slots[i] = NULL;
		}
	}

	system("pause");
	return 0;
}

char get_block(void)
{
	char block;
	cout << "Enter one block: " << endl;
	cin >> block;
	return toupper(block);
}

void print_slots(char slots[])
{
	unsigned int j = 1;
	for (j = 1; j <= 20; j++)
	{
		cout << setw(3) << j;
	}
	cout << endl;
	for (j = 0; j < 20; j++)
	{
		cout << setw(3) << slots[j];
	}
	cout << endl;
	return;
}

unsigned int put_block(char block, unsigned int position, char array[])
{
	bool debug = false;
	array[position] = block;
	if (debug)
		cout << "Block " << block << " inserted into slot " << (position + 1) << endl;
	return position;
}

unsigned int calc_right_bound(char robot, unsigned int position, char array[]) {
	unsigned int right_bound = position;
	bool debug = false;
	while (right_bound < 19) {
		position = shift_right(right_bound);
		if (!test_empty(position, array) && robot_eq_slot(robot, array[position])) {
			right_bound++;
		}
		else {
			right_bound++;
			break;
		}
	}
	if (debug) {
		cout << "The right bound calculated is slot " << (right_bound + 1) << endl << endl;
	}
	return right_bound;
}

unsigned int remove_block(unsigned int position, char array[])
{
	bool debug = false;
	char block = ' ';
	block = array[position];
	array[position] = ' ';
	if (debug)
		cout << "Block " << block << " removed from slot " << (position + 1) << endl;
	return block;
}

unsigned int shift_right(unsigned int position)
{
	bool debug = false;
	position++;
	if (debug)
		cout << "Position right shifted to " << (position + 1) << endl;
	return position;
}

unsigned int shift_left(unsigned int position)
{
	bool debug = false;
	position--;
	if (debug)
		cout << "Position left shifted to " << (position + 1) << endl;
	return position;
}

unsigned int shuffle_to(unsigned int position, unsigned int target) {
	bool debug = false;
	unsigned int i = 0;
	if (target < 0 || target > 19) {
		cout << "Error: Cannot shuffle to index because index is out of range." << endl;
		system("pause");
	}
	if (target < position) {
		for (i = (position - target); i > 0; i--) {
			position = shift_left(position);
		}
		if (debug) {
			cout << "Position shuffled left to " << (position + 1) << endl;
		}
	}
	else if (target > position) {
		for (i = (target - position); i > 0; i--) {
			position = shift_right(position);
		}
		if (debug) {
			cout << "Position shuffled right to " << (position + 1) << endl;
		}
	}
	return position;
}

bool robot_ltoreq_slot(char robot, char in_slot)
{
	bool debug = false;
	if (debug)
		cout << endl << "Comparing robot block " << robot << " with block in slot " << in_slot << endl;
	if (robot <= in_slot)
	{
		if (debug)
			cout << "Returning true. Robot block LESS than or EQUAL to block in slot. " << endl;
		return true;
	}
	else
	{
		if (debug)
			cout << "Returning false. Robot block GREATER than block in slot. " << endl;
		return false;
	}
}

bool robot_eq_slot(char robot, char in_slot)
{
	bool debug = false;
	if (debug)
		cout << endl << "Comparing robot block " << robot << " with block in slot " << in_slot << endl;
	if (robot == in_slot)
	{
		if (debug)
			cout << "Returning true. Robot block EQUAL to block in slot. " << endl;
		return true;
	}
	else
	{
		if (debug)
			cout << "Returning false. Robot block not equal to block in slot. " << endl;
		return false;
	}
}

bool min_switch(unsigned int left_bound, unsigned int right_bound, char array[]) {
	unsigned int left = 0, right = 0;
	bool debug = false;
	while (!test_empty(right_bound, array)) {
		if (right_bound == 19) {
			if (debug)
				cout << "Moving left because cannot move right" << endl;
			return false;
		}
		right++;
		right_bound = shift_right(right_bound);
	}
	left_bound = shuffle_to(right_bound, left_bound);
	while (!test_empty(left_bound, array)) {
		if (left_bound == 0) {
			if (debug)
				cout << "Moving right because cannot move left" << endl;
			return true;
		}
		left++;
		left_bound = shift_left(left_bound);
	}
	if (right <= left) {
		if (debug && (right != left))
			cout << "Minimum switches moving right, " << (left - right) << " fewer shifts" << endl;
		else if(debug)
			cout << "Moving right requires the same number of shifts as moving left, so moving right" << endl;
		right_bound = shuffle_to(left_bound, right_bound);
		return true;
	}
	if (debug)
		cout << "Minimum switches moving left, " << (right - left) << " fewer shifts" << endl;
	return false;
}

unsigned int insert_block(unsigned int left_bound, char block, char array[]) {
	bool debug = false;
	unsigned int right_bound = calc_right_bound(block, left_bound, array);
	if (test_empty(right_bound, array)) {
		if (debug)
			cout << "Right bound empty, placing block in slot " << (right_bound + 1) << endl;
		put_block(block, right_bound, array);
		return right_bound;
	}
	if (min_switch(left_bound, right_bound, array)) {
		while (!test_empty(right_bound, array)) {
			block = switch_blocks(block, right_bound, array);
			right_bound = shift_right(right_bound);
			swap_count++;
		}
		return put_block(block, right_bound, array);
	}
	else {
		while (!test_empty(left_bound, array)) {
			block = switch_blocks(block, left_bound, array);
			left_bound = shift_left(left_bound);
			swap_count++;
		}
		return put_block(block, left_bound, array);
	}
}

char switch_blocks(char robot, unsigned int position, char array[])
{
	char temp_hold;
	bool debug = false;
	if (debug)
		cout << "Switching blocks " << robot << " with " << array[position] << endl;
	temp_hold = robot;
	robot = array[position];
	array[position] = temp_hold;
	return robot;
}

bool test_empty(unsigned int position, char array[])
{
	char blank = ' ';
	bool debug = false;
	if (array[position] == NULL || array[position] == blank)
	{
		if (debug)
			cout << "Slot " << (position + 1) << " empty. " << endl;
		return true;
	}
	else
	{
		if (debug)
			cout << "Slot " << (position + 1) << " contains a block " << endl;
		return false;
	}

}

char get_block_testcase(unsigned int testcase, unsigned int index)
{
	string testcases[5] = { "AXFIUTRPQVWSEYJINYTB",
		"ABFGHIJKMOPRSTUVWXYZ",
		"ZYXWVUTSRPOKJIIHGFBA",
		"AAAAAYYYYYQQQQQXXXXX",
		"XXXAAAZZZAAYYVVVVQQQ" };

	return testcases[testcase - 1].at(index);
}

char get_block_testone(void)
{
	static unsigned int index = 0;
	char test_case_one[21] = "AXFIUTRPQVWSEYJINYTB";
	return test_case_one[index++];
}

char get_block_testtwo(void)
{
	static unsigned int index = 0;
	char test_case_two[21] = "ABFGHIJKMOPRSTUVWXYZ";
	return test_case_two[index++];
}

char get_block_testthree(void)
{
	static unsigned int index = 0;
	char test_case_three[21] = "ZYXWVUTSRPOKJIIHGFBA";
	return test_case_three[index++];
}

char get_block_testfour(void)
{
	static unsigned int index = 0;
	char test_case_four[21] = "AAAAAYYYYYQQQQQXXXXX";
	return test_case_four[index++];
}

char get_block_testfive(void)
{
	static unsigned int index = 0;
	char test_case_five[21] = "XXXAAAZZZAAYYVVVVQQQ";
	return test_case_five[index++];
}