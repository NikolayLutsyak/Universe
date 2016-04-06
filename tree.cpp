node * Tree::find_node(int key, node * root)
{	
	
    if (!root)
		exit(EXIT_FAILURE);
    
    if (root->key == key)
        return root;
    else
    {
		if (root->leaf == 1)
		{
			return NULL;
        }
        
        int N = root->child.size();
        int i = 0;
        for (i=0; i<N; i++)
        {
			if(root->child[i])
            {
				if(find_node(key,root->child[i]))
					return find_node(key,root->child[i]);
			}
        }
    }
};
