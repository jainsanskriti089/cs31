#include <iostream>
#include <string>
#include <cctype>
#include <cassert>

using namespace std;

bool hasRightSyntax(string pollData);
int computeVotes(string pollData, char party, int& voteCount);
bool isValidUppercaseStateCode(string stateCode);
int processStateVotes(char party, string pollData, int& i, int& voteTally);

int main() {
    //true cases
    assert(hasRightSyntax(""));                 //empty string
    assert(hasRightSyntax("R40TXD54CA"));       //given test case
    assert(hasRightSyntax("r4tx"));             //single state prediction (lower case)
    assert(hasRightSyntax("r4txd3ca"));         //two state predictions (lower case)
    assert(hasRightSyntax("r40txd30cal7fl"));   //three state predictions (lower case)
    assert(hasRightSyntax("D40CAT43NYP20NM"));  //three state predictions (upper case)
    assert(hasRightSyntax("r04tx"));            //number that starts with 04
    assert(hasRightSyntax("r00tx"));            //number 0 written as 00

    //false cases
    assert(!hasRightSyntax("R40MXD54CA"));     //given test case
    assert(!hasRightSyntax("rtx"));            //no number (single state prediction)
    assert(!hasRightSyntax("d400ca"));         //3 digit number (single state prediction)
    assert(!hasRightSyntax("d400"));           //3 digit number, incomplete (single state prediction)
    assert(!hasRightSyntax("d30txr004CA"));    //3 digit number in the second state prediction (two state predictions)
    assert(!hasRightSyntax("d"));              //1 letter (incomplete state prediction)
    assert(!hasRightSyntax("d400c8"));         //3 digit number, invalid state code (single state prediction)
    assert(!hasRightSyntax("r4car4223tx"));    //4 digit number (two state predictions)
    assert(!hasRightSyntax("4car43tx"));       //starts with a digit --> no party letter
    assert(!hasRightSyntax("r30xy"));          //invalid state code but correct order
    assert(!hasRightSyntax("r30dcd30"));       //missing final state code, incomplete (two state predictions)
    assert(!hasRightSyntax("r$tx"));           //symbol in the state prediction
    assert(!hasRightSyntax("d 45 ca"));        //spaces
    assert(!hasRightSyntax("dd45ca"));         //starts with two letters
    assert(!hasRightSyntax("d45caaz30dc"));    //2 letters following a state code that also form a valid state code

    int votes;
    votes = -999;
    assert(computeVotes("R40TXD54CAr6Msd28nYL06UT", 'd', votes) == 0 && votes == 82);    //given test case
    votes = -999;
    assert(computeVotes("R40TXD54CA", '%', votes) == 3 && votes == -999);                //given test case
    assert(computeVotes("", 'R', votes) == 0 && votes == 0);                             //empty string sets votes to 0
    votes = -999;
    assert(computeVotes("r40dc30", 'R', votes) == 1 && votes == -999);                   //invalid syntax, leaves votes unchanges 
    votes = -999;
    assert(computeVotes("r04tx", 'R', votes) == 0 && votes == 4);                        //computes numbers that start with 0 correctly
    assert(computeVotes("r0ca", 'R', votes) == 2 && votes == 4);                         //state prediction has 0 electoral votes
    assert(computeVotes("r0cad0tx", 'R', votes) == 2 && votes == 4);                     //state prediction has 0 electoral votes even if incorrect party
    assert(computeVotes("r00ca", 'R', votes) == 2 && votes == 4);                        //state prediction has 0 electoral votes written as 00
}

bool hasRightSyntax(string pollData) {
    //cerr << "checking: " << pollData << endl; --> indicates what test case was being checked for debugging purposes
    if (pollData == "") return true;
    for (int i = 0; i < pollData.size(); i++) {                             //adjusts the string to be all uppercase (easier to check)
        pollData[i] = toupper(pollData[i]);
    }

    if (pollData.size() < 4) return false;                                  //can not be a complete poll data string and won't go through the loop (e.g. size = 1)

    int i = 0;

    while (i < pollData.size()) {
        // Check if the character at position i is a letter (party code)
        if (!isalpha(pollData[i])) {
            return false; // Invalid if it's not a letter
        }
        i++; // Move to the next character after party code

        // Check for 1 or 2 digits representing vote count
        if (i < pollData.size() && isdigit(pollData[i])) {
            i++;
            if (i < pollData.size() && isdigit(pollData[i])) {
                i++;
            }
        }
        else {
            return false; // Invalid if no digits follow the party code
        }

        // Check if the next two characters form a valid state code
        if (i + 1 < pollData.size() && isValidUppercaseStateCode(pollData.substr(i,2)))
            i += 2; // Move past the state code
        else
            return false; // Invalid if state code is not two letters
    }
    return true;
}

int computeVotes(string pollData, char party, int& voteCount) {
    if (!hasRightSyntax(pollData)) return 1;                               //pollData parameter does not have the right syntax --> return 1
    if (!isalpha(party)) return 3;                                         //party parameter is not a letter --> return 3

    party = toupper(party);
    for (int i = 0; i < pollData.size(); i++) {
        pollData[i] = toupper(pollData[i]);
    }

    int j = 0;
    int size = pollData.size();
    int addVotes = 0;
    while (j < size - 1) {
        if (isdigit(pollData.at(j + 1))) {
            int status = processStateVotes(party, pollData, j, addVotes);
            if (status == -1) return 2;                                    //votes for that state prediction amount to 0 --> return 2
        }
        else j++;
    }
    voteCount = addVotes;
    return 0;                                                             //everything was fine, set voteCount --> return 0
}

bool isValidUppercaseStateCode(string stateCode)
{
    const string codes =
        "AL.AK.AZ.AR.CA.CO.CT.DE.DC.FL.GA.HI.ID.IL.IN.IA.KS."
        "KY.LA.ME.MD.MA.MI.MN.MS.MO.MT.NE.NV.NJ.NH.NM.NY.NC."
        "ND.OH.OK.OR.PA.RI.SC.SD.TN.TX.UT.VT.VA.WA.WV.WI.WY";
    return (stateCode.size() == 2 &&
        stateCode.find('.') == string::npos &&  // no '.' in stateCode
        codes.find(stateCode) != string::npos);  // match found
}

int processStateVotes(char party, string data, int& i, int& voteTally) {
    char currParty = data.at(i);
    i++;
    int votes = 0;
    while (isdigit(data.at(i))) {
        votes = votes * 10 + (data.at(i) - '0');                         //convert string of numbers into the respective integer
        i++;
    }
    i += 2;                                                              //increment past the following state code, setting the index to the next state prediction
    
    if (votes == 0) return -1;                                           //indicates to computeVotes that the total number of votes for that state prediction is 0 so that it can return 2 and terminate
    
    if (party != currParty) return -2;                                   //doesn't add the votes if the party of the state prediction doesn't match the party being counted
    voteTally += votes;
    return 0;                                                            //everything was fine, adjusted the number of votes with that state prediction's contribution
}