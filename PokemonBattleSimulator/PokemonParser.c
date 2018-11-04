#include "PokemonParser.h"

//ADD IN ERROR HANDELING LATER

void inputPokemon(Pokedex** newPokedex){
  FILE * fp;



  fp = fopen("pokedex.txt","r");

  List * includedPokemon = initializeList(printPokemonBase, deletePokemonBase, comparePokemonBase);

  fclose(fp);

  fp = fopen("moves.txt","r");

  fclose(fp);

  fp = fopen("teamA.txt","r");

  fclose(fp);

  fp = fopen("teamB.txt","r");

  fclose(fp);














}


void deletePokemonBase(Pokedex** pokedex){

}
int comparePokemonBase(const void* first, const void* second){
return 0;
}
void printPokemonBase(Pokedex** pokedex){

}

void deleteMove(Pokedex** pokedex){

}
int compareMoves(const void* first, const void* second){
  return 0;
}
void printMove(Pokedex** pokedex){

}

void deleteUserPokemon(Pokedex** pokedex){

}
int compareUserPokemon(const void* first, const void* second){
  return 0;
}
void printUserPokemon(Pokedex** pokedex){

}
