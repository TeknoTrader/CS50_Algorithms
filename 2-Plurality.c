#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
} candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    bool a;
    for (int i = 0; i < candidate_count; i++) // Let's chack the names of the candidates
    {
        if (strcmp(candidates[i].name, name) == 0) // Check if the name corrisponds
        {
            a = true; // name found in the list
            candidates[i].votes++;
            break;
        }
        else
        {
            a = false; // name not found
        }
    }
    return a;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    int winnerN = 0; // The greatest amount of points earned
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > winnerN)
        {
            winnerN = candidates[i].votes;
        }
    }
    int winners_counter = 0;
    for (int i = 0; i < candidate_count; i++) // Number of candidates that wons
    {
        if (candidates[i].votes == winnerN)
        {
            winners_counter++;
        }
    }

    string winners[winners_counter]; // Who won?
    int counter = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == winnerN)
        {
            winners[counter] = candidates[i].name;
            counter++;
        }
    }

    for (int i = 0; i < winners_counter; i++) // Finally printing
    {
        printf("%s\n", winners[i]);
    }
    if (winners_counter == 0) // To avoid errors due to lack of votes
    {
        for (int i = 0; i < candidate_count; i++)
        {
            printf("%s\n", candidates[i].name);
        }
    }
}
