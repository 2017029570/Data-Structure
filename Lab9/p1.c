#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct _DisjointSet {
		  int size_maze;
		    int *ptr_arr;
} DisjointSets;

void init(DisjointSets *sets, DisjointSets *maze_print, int num);
void Union(DisjointSets *sets, int i, int j);
int find(DisjointSets *sets, int i);
void createMaze(DisjointSets *sets, DisjointSets *maze_print, int num);
void printMaze(DisjointSets *maze_print, int num);
void freeMaze(DisjointSets *sets, DisjointSets *maze_print);

int main(int argc, char const *argv[]) {
		  int num, i;
		    FILE *fi = fopen(argv[1], "r");
			  DisjointSets *sets, *maze_print;
			    fscanf(fi, "%d", &num);
				  sets = (DisjointSets*) malloc(sizeof(DisjointSets));
				    maze_print = (DisjointSets*) malloc(sizeof(DisjointSets));
					  init(sets, maze_print, num);
					    createMaze(sets, maze_print, num);
						  printMaze(maze_print, num);
						    freeMaze(sets, maze_print);

							  fclose(fi);
							    return 0;
}

void init(DisjointSets *sets, DisjointSets *maze_print, int num) {
		  sets->size_maze = num*num;
		    sets->ptr_arr = (int*) malloc(sizeof(int) * sets->size_maze);
			  for(int i = 0; i < sets->size_maze; i++) {
					      sets->ptr_arr[i] = -1;
						    }
			    maze_print->size_maze = (2*num+1)*(2*num+1);
				  maze_print->ptr_arr = (int*) malloc(sizeof(int) * maze_print->size_maze);
				    for(int i = 0; i < maze_print->size_maze; i++) {
							    if(i % (4 * num + 2) < 2 * num + 1 && i % 2 == 1) maze_print->ptr_arr[i] = 1; //means "-"
								    else if(i % (4 * num + 2) >= 2 * num + 1 && i % 2 == 1) maze_print->ptr_arr[i] = 2; //means "|"
									    else if(i % (4 * num + 2) >= 2 * num + 1 && i % 2 == 0) maze_print->ptr_arr[i] = 0; 
										    else maze_print->ptr_arr[i] = -1; 
											  }
					  maze_print->ptr_arr[2 * num + 1] = -1;
					    maze_print->ptr_arr[maze_print->size_maze - 2 * num - 2] = -1;
}

void Union(DisjointSets *sets, int i, int j) {
		  sets->ptr_arr[find(sets,j)] = find(sets,i);
}

int find(DisjointSets *sets, int i) {
		  if(sets->ptr_arr[i] == -1) {
				      return i;
					    }
		    else {
					    return find(sets, sets->ptr_arr[i]);
						  }
}

void createMaze(DisjointSets *sets, DisjointSets *maze_print, int num) {

		  int nMAX = (2*num+1)*(2*num+1);
		    srand( time(NULL) );            

			  int *nLottoNum = (int*)malloc(sizeof(int)*nMAX);
			    for(int i = 0; i< nMAX; i++) {
						    nLottoNum[i] = 0;
							  }             
				  int *bCheckExistOfNum = (int*)malloc(sizeof(int)*nMAX);
				    for(int i = 0; i < nMAX; i++) {
							    bCheckExistOfNum[i] = 0;   
								  }
					  
					  for( int i=0 ; i<nMAX ; )           
							    {
										    int nTemp = rand()%nMAX;                  
											    if( bCheckExistOfNum[nTemp] == 0 ) 
														    {
																	      bCheckExistOfNum[nTemp] = 1;  
																		        nLottoNum[i] = nTemp;   
																				      ++i;              
																					      }
												  }

					    
					    

					    int a = 1;
						  int random = -1;
						    while(a == 1) {
									    random++;
										    int b = 1;
											//select random wall's ptr

											    int random_gen = nLottoNum[random];
												    while( maze_print->ptr_arr[random_gen] <= 0 || random_gen < 2*num+1 || random_gen > maze_print->size_maze - 2*num - 1
																	    || random_gen % (2*num+1) == 0 || random_gen % (2*num+1) == 2*num ) {
															      if(random >= nMAX){
																		          b = 0;
																				          a = 0;
																						          break;
																								        }
																        //printf("%d, %d\n",random,random_gen);
																        random_gen = nLottoNum[++random];
																		    }
													    if(b == 1){
																      if(maze_print->ptr_arr[random_gen] == 1) {
																			          int upper_pm = random_gen - (2*num+1);
																					          int lower_pm = random_gen + 2*num+1;

																							          int upper_m = (upper_pm%(2*num+1)+1)/2-1 + ((upper_pm/(2*num+1)+1)/2-1)*num;
																									          int lower_m = (lower_pm%(2*num+1)+1)/2-1 + ((lower_pm/(2*num+1)+1)/2-1)*num;
																											          //printf("upper_m: %2d         lower_m: %2d\n",upper_m,lower_m);
																											          if(find(sets, upper_m) != find(sets, lower_m)) {
																															            Union(sets, upper_m, lower_m);
																																		          maze_print->ptr_arr[random_gen] = -1;
																																				          }

																													        }else if(maze_print->ptr_arr[random_gen] == 2){
																																	        int left_pm = random_gen - 1;
																																			        int right_pm = random_gen + 1;

																																					        int left_m = (left_pm%(2*num+1)+1)/2-1 + ((left_pm/(2*num+1)+1)/2-1)*num;
																																							        int right_m = (right_pm%(2*num+1)+1)/2-1 + ((right_pm/(2*num+1)+1)/2-1)*num;
																																									        //printf("left_m: %2d         right_m: %2d\n",left_m,right_m);
																																									        if(find(sets, left_m) != find(sets, right_m)) {
																																													          //printf("%d != %d\n",find(sets,left_m),find(sets,right_m));
																																													          Union(sets, left_m, right_m);
																																															            maze_print->ptr_arr[random_gen] = -1;
																																																		        }
																																											      }else printf("error: didn't choose wall. check algorithm.\n");

																	        int check = -1;
																			      for(int i = 0; i < sets->size_maze; i++) {
																						          check = find(sets, i);
																								          if(check != 0) break;
																										          if(i == sets->size_maze - 1) a = 0;
																												        }
																				      }
														  }
}

void printMaze(DisjointSets* maze_print, int num) {
		  for(int i = 0; i < maze_print->size_maze; i++){
				      if(i / (2 * num + 1) != 0 && i % (2 * num + 1) == 0) printf("\n");
					      if(maze_print->ptr_arr[i] == 1) printf("-");
						      else if(maze_print->ptr_arr[i] == 2) printf("|");
							      else printf (" ");
								    }
		    printf("\n");
}


void freeMaze(DisjointSets *sets, DisjointSets *maze_print) {
		  free(sets);
		    free(maze_print);
} 

