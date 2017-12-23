#include "b_tree.h"

void b_tree::insert (Point2i p, float score) 
{
	if(this->base == NULL)
	{
		base = new feature;
		base->left = base->right = NULL;
		base->p = p;
		base->score = score;
		tam++;
	}
	else
	{
		act = this->base;
		act = insert(act,p,score);
	}
}

feature* b_tree::insert (feature* nodo, Point2i p, float score) 
{
	int dist;
	if(nodo == NULL)
	{
		nodo = new feature;
		nodo->left = nodo->right = NULL;
		nodo->p = p;
		nodo->score = score;
		
		tam++;
	}
	else
	{
		// Esta muy cerca, y tiene mayor puntaje -> Reemplazo (revisar criterio)
		if(score > nodo->score)
		{
			dist = norm(nodo->p - p);
			if(dist<20)
			{
				nodo->p = p; nodo->score = score;
			}
			else
			{
				nodo->left = insert(nodo->left,p,score);
			}
		}
		else
		{
			dist = norm(nodo->p - p);
			if(dist>20)
			{
				nodo->right = insert(nodo->right,p,score);
			}
			
		}
	}
	
	return nodo;
}

vector<Point2i> b_tree::get_tree () {
	
	if(base->left != NULL)
	{
		get_tree(base->left);
	}
	
	pasaje.push_back(base->p);

	if(base->right!= NULL)
	{
		get_tree(base->right);
	}
	
	return pasaje;
//	return vec_p;
}

void b_tree::get_tree (feature * nodo) {
	
	if (nodo == NULL)
	{
		return;
	}
	
	if(nodo->left != NULL)
	{
		get_tree(nodo->left);
	}
	
	pasaje.push_back(nodo->p);
	
	if(nodo->right!= NULL)
	{
		get_tree(nodo->right);
	}
	
}

Point2i b_tree::get (feature * nodo) {
	return nodo->p;
}

int b_tree::get_size ( ) {
	
//	return get_size(base);
	return tam;
}

int b_tree::get_size (feature * nodo) {
	
	int size;
	
	if(nodo == NULL)
	{
		size = 0;
	}
	else
	{
		size =  get_size(nodo->left) + 1 + get_size(nodo->right);
	}
	
	return size;
}

void b_tree::erase (Point2i p) {
	if (base->p == p){
		
		if(left!=NULL)
		{
			
		}
		
	}
}

feature * b_tree::erase (feature * nodo, Point2i p) {
	
}

