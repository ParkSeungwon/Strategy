#include "time.h"
Time::Time(){}
int Time::oneTurnPass()
{
	for(int k=0; k < turn; k++) {
		for(int i=0; i<MAX_TEAM; i++) {
			for(int j=0; j<MAX_UNIT; j++) {
				deployed_units[i][j]->time_pass(one_tick * k);//유닛 위치 이동, 정찰, 무기 범위 갱신
				deployed_units[i][j]->adjust_recon();
				deployed_units[i][j]->weapon
				deployed_units[i][j]->
			}
		}
		for(int i=0; i<MAX_TEAM; i++) {
			for(int j=0; j<MAX_UNIT; j++) {
				deployed_units[i][j]->attck();//공격
			}
		}
	}
	return 0;
}

Time::end_turn()
{//eliminate destroyed units from array queue
	if(deployed_units[target]->currentHealth <= 0) {
		delete e[terget];//유닛큐를 비우고 뒤에서 채워 넣는다.
		e[target] = e[i-1];
		e[i-1] = NULL;
	}


