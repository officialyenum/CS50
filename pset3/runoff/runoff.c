#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // TODO
    //iterate through each candidate
    for (int i = 0; i < candidate_count; i++)
    {
        //check if given name is existing candidate
        if (strcmp(name, candidates[i].name) == 0)
        {
            //if name matches - add vote choice to correct location in 2-dimentional array preferences[voter][rank]
            preferences[voter][rank] = i;
            return true;
        }
        //when preference array is updated you must return true
        //return true;
    }
    //else return false (i.e name not a candidate)
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // TODO
    // iterate through voter count (i.e i voters)
    for (int i = 0; i < voter_count; i++)
    {
        // determine whether in rank 1 or 2
        int j = 0;

        // check through each vote in rank 1 if eliminated
        while (candidates[preferences[i][j]].eliminated == true)
        {

            // if eliminated
            // access rank 2 by increasing j
            j++;
        }
        // then check the candidate
        // add vote +1
        // if not eliminated add +1 vote for rank1 voted candidate
        candidates[preferences[i][j]].votes++;
    }
    // end
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // TODO
    bool winner;
    // half the total vote count and create a new variable
    int majority = voter_count / 2 + 0.5;
    // iterate through the candidates to check each one
    for (int i = 0; i < candidate_count; i++)
    {
        // check if the candidate's total votes is more than half of the vote count
        if (candidates[i].votes > majority)
        {
            // if it is then they are the winner
            winner = true;
            // print candidate name
            printf("%s\n", candidates[i].name);
            //return true
            return winner;
        }
    }
    // if none of the candidates total votes is more than half the total vote count
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // TODO
    //Make a lowestVote variable and equal it to the first candidate vote total
    int lowestVoteNum = candidates[0].votes;
    //check through each candidate
    for (int m = 0; m < candidate_count; m++)
    {
        //check whether candidate is still in the game
        //if candidate is still in game
        //check whether current candidate total vote is more than the next candidate total vote
        if (candidates[m].eliminated == false && lowestVoteNum > candidates[m].votes)
        {
            //if first candidate total vote is bigger than next candidate update lowestVote variable equal to next candidate total vote
            lowestVoteNum = candidates[m].votes;

        }
        //the loop will keep iterating through candidates
    }
    //return lowestVote total
    return lowestVoteNum;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        //check if candidate is eliminated
        if (candidates[i].eliminated)
        {
            continue;
        }
        //check if candidate total vote is the same as the smallest vote total
        else if (min == candidates[i].votes)
        {
            continue;
        }
        else
        {
            return 0;
        }
    }
    return 1;
}

// Eliminate the candidate (or candidiates) in last place
void eliminate(int min)
{
    // TODO

    //iterate through the candidates
    for (int n = 0; n < candidate_count; n++)
    {
        //if the candidate vote equals the 'min' (smallest number of votes) and are also still in the game (not eliminated)
        if (!candidates[n].eliminated && candidates[n].votes == min)
        {
            //then eliminate them
            candidates[n].eliminated = true;
        }
    }
    return;
}
