#include <math.h>
#include <stdlib.h>

#define UCB_PARAM 0.25

#define min(x, y) ((x < y)? x : y)

typedef struct {
    int *arms;
    int *reward;
    int *variance;
    int *used_times;
    int length;
    int total_times;
    double *ucb_values;
} Bandit;

Bandit* initial_bandit(int length) {
    int *current_arms          =  (int *) malloc(sizeof(int) * length);
    int *current_reward        =  (int *) malloc(sizeof(int) * length);
    int *current_variance      =  (int *) malloc(sizeof(int) * length);
    int *current_used_times    =  (int *) malloc(sizeof(int) * length);
    double *current_ucb_values =  (double *) malloc(sizeof(double) * length);

    for (int i = 0; i < length; i ++) {
        current_arms[i]       = i;
        current_reward[i]     = 0;
        current_variance[i]   = 0;
        current_ucb_values[i] = 1000.0;
        current_used_times[i] = 0;
    }

    Bandit *bandit   = (Bandit *) malloc(sizeof(Bandit));
    bandit->arms     = current_arms;
    bandit->reward   = current_reward;
    bandit->variance = current_variance;

    bandit->ucb_values  = current_ucb_values;
    bandit->used_times  = current_used_times;
    bandit->length      = length;
    bandit->total_times = 0;

    return bandit;
}

int select_maximum_arms(Bandit *bandit) {
    double max = -1;
    int max_arms = -1;
    for (int i = 0; i < bandit->length; i ++) {
        if (bandit->ucb_values[i] > max) {
            max = bandit->ucb_values[i];
            max_arms = i;
        }
    }
    return bandit->arms[max_arms];
}


double get_variance_ucb(int selected_arms, Bandit *bandit) {

    int arm = bandit->arms[selected_arms];

    double ucb_component = sqrt((2 * log((double) bandit->total_times)) / bandit->used_times[arm]);

    double mean     = (double) bandit->reward[arm] / (bandit->used_times[arm] + 0.0);
    double variance = (double)bandit->variance[arm] / (bandit->used_times[arm] + 0.0) - mean * mean;

    return variance + ucb_component;
}



Bandit *update_arms(int selected_arms, int reward, Bandit *bandit) {
    int arm = bandit->arms[selected_arms];

    bandit->reward[arm]   += reward;
    bandit->variance[arm] += reward * reward; 

    bandit->used_times[arm] ++;
    bandit->total_times ++;

    double tune_component = min(UCB_PARAM, get_variance_ucb(selected_arms, bandit));
    
    bandit->ucb_values[arm] = sqrt((tune_component * log((double) bandit->total_times)) / bandit->used_times[arm])
                              + (double) bandit->reward[arm] / (bandit->used_times[arm] + 0.0); 
    return bandit;
}