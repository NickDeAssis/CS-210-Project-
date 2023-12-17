/*
Nicolas DeAssis
11/20/2023
CS - 210 - Bank project
*/

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

void DisplayMenu(double& initInvestment, double& monthlyDeposit, double& annualInterestRate, int& numOfYears){ // use this function to both display the intial menu and get data from user using pass by reference
	
	bool validNums = false;
	
	while (!validNums) {// error handling making sure that the values for each field are greater than 0 (positive numbers)
		cout << setfill('*') << setw(36) << "*" << endl;
		cout << setw(23) << " Data Input " << right << setw(13) << "*" << endl; // this section displays the header using formatting manipulation

		//This block of code below gathers the user inputed information and validates the values added
		cout << "Initial Investment Amount: $";
		cin >> initInvestment;
		if (initInvestment < 0) {
			cout << "Invald value please try again" << endl << endl;
			continue;
		}

		cout << "Monthly Deposit: $";
		cin >> monthlyDeposit;
		if (monthlyDeposit < 0) {
			cout << "Invald value please try again" << endl << endl;
			continue;
		}

		cout << "Annual Interest Rate: %";
		cin >> annualInterestRate;
		if (annualInterestRate < 0) {
			cout << "Invald value please try again" << endl << endl;
			continue;
		}

		cout << "Number of Years: ";
		cin >> numOfYears;
		if (numOfYears < 0) {
			cout << "Invald value please try again" << endl << endl;
			continue;
		}

		validNums = true;// leave the loop as we have valid inputs
			cout << setfill('*') << setw(36) << "*" << endl;
	}
}

class Report {
public:
	void DisplayReport(double initInvestment, double monthlyDeposit, double annualInterestRate, int numOfYears) const;
};

void Report::DisplayReport(double initInvestment, double monthlyDeposit, double annualInterestRate, int numOfYears) const{ // Displays the 2 reports on using customer inputs

		// variables to help display the WITHOUT reporting
		double withoutAdditionsYearEndBalance = initInvestment;
		double withoutAdditionsYearEndEarnedInterest = 0.0;

		// Display for the first report (Without Additions)
		cout << endl;// this section is the header for report 1
		cout << "       Balance and Interest Without Additional Monthly Deposits" << endl;
		cout << setfill('=') << setw(70) << "=" << endl;
		cout << setfill(' ') << right << setw(9) << "Year" << setw(24) << "Year End Balance" << setw(32) << "Year End Earned Interest" << endl;
		cout << setfill('-') << setw(70) << "-" << endl;

		for (int i = 1; i <= numOfYears; i++) {// loop for report without the additional monthly additions calculates the respective outputs

			withoutAdditionsYearEndEarnedInterest = withoutAdditionsYearEndBalance * (annualInterestRate / 100);
			withoutAdditionsYearEndBalance += withoutAdditionsYearEndBalance * (annualInterestRate / 100);

			cout << fixed << setprecision(2) << setfill(' ') << setw(9) << i << setw(24) << withoutAdditionsYearEndBalance << setw(32) << withoutAdditionsYearEndEarnedInterest << endl;
		}
		cout << setfill('-') << setw(70) << "-" << endl;// Segment end


		// Display for the second report (With Additions)
		// variables to help display the WITH reporting
		double withAdditionsYearEndBalance = 0.0;
		double withAdditionsYearEndEarnedInterest = 0.0;
		//variables for the inner loop montly calculations
		double totalOfMonth = 0.0;
		double monthlyInterestEarned = 0.0;
		double totalMonthlyInterestEarned = 0.0;
		double monthlyClosingBalance = initInvestment;


		cout << endl; // display header for report 2
		cout << "       Balance and Interest With Additional Monthly Deposits" << endl;
		cout << setfill('=') << setw(70) << "=" << endl;
		cout << setfill(' ') << right << setw(9) << "Year" << setw(24) << "Year End Balance" << setw(32) << "Year End Earned Interest" << endl;
		cout << setfill('-') << setw(70) << "-" << endl;

		for (int i = 1; i <= numOfYears; i++) {// loop for report with the additional monthly additions
			for (int x = 1; x <= 12; x++) {// nested loop for the monthly calculations

				totalOfMonth = monthlyClosingBalance + monthlyDeposit;

				monthlyInterestEarned = totalOfMonth * (annualInterestRate / 100 / 12);
				totalMonthlyInterestEarned += monthlyInterestEarned;
				monthlyClosingBalance = totalOfMonth + monthlyInterestEarned;
			}
			withAdditionsYearEndBalance = monthlyClosingBalance;
			withAdditionsYearEndEarnedInterest = totalMonthlyInterestEarned;
			cout << fixed << setprecision(2) << setfill(' ') << setw(9) << i << setw(24) << withAdditionsYearEndBalance << setw(32) << withAdditionsYearEndEarnedInterest << endl;
			totalMonthlyInterestEarned = 0;
		}
	cout << setfill('-') << setw(70) << "-" << endl;// segemtn end
}

int main() {
	// variables declared for bank program
	Report userReport;
	double initInvestment;
	double monthlyDeposit;
	double annualInterestRate;
	int numOfYears;
	bool runProgram = true;
	int rerunInt = 1;

	while (runProgram) {// this keeps the program running untill user decieds to end
		DisplayMenu(initInvestment, monthlyDeposit, annualInterestRate, numOfYears);// Displays Menu function
		userReport.DisplayReport(initInvestment, monthlyDeposit, annualInterestRate, numOfYears); // Display the Reports using the class created

		cout << "Type 1 to rerun the program" << endl;
		cout << "Type 2 to terminate the program" << endl;
		cin >> rerunInt;
		cout << endl;

		if (rerunInt == 1) { // allows for user to continue or escape program
			runProgram = true;
		}
		else {
			runProgram = false;
		}
	}
	return 0;
}