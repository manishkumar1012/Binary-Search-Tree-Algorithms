
//-----------1. Kth Smallest element in a bst-------

int kthSmallest(TreeNode* root, int k) {
    stack<TreeNode*> treeStack;
    while (true) {
        while (root) {
            treeStack.push(root);
            root = root->left;
        }
        root = treeStack.top();
        treeStack.pop();
        if (--k == 0) {
            return root->val;
        }
        root = root->right;
    }
}


//------------2. Pair with given sum in a bst-------------

time - O(n), Space - O(h)
bool isPairPresent(node* root, int target)
{
    // Create two stacks. s1 is used for
    // normal inorder traversal and s2 is
    // used for reverse inorder traversal
    Stack* s1 = createStack(MAX_SIZE);
    Stack* s2 = createStack(MAX_SIZE);

    // Note the sizes of stacks is MAX_SIZE,
    // we can find the tree size and fix stack size
    // as O(Logn) for balanced trees like AVL and Red Black
    // tree. We have used MAX_SIZE to keep the code simple

    // done1, val1 and curr1 are used for
    // normal inorder traversal using s1
    // done2, val2 and curr2 are used for
    // reverse inorder traversal using s2
    bool done1 = false, done2 = false;
    int val1 = 0, val2 = 0;
    node *curr1 = root, *curr2 = root;

    // The loop will break when we either find a pair or one of the two
    // traversals is complete
    while (1) {
        // Find next node in normal Inorder
        // traversal. See following post
        // https:// www.geeksforgeeks.org/inorder-tree-traversal-without-recursion/
        while (done1 == false) {
            if (curr1 != NULL) {
                push(s1, curr1);
                curr1 = curr1->left;
            }
            else {
                if (isEmpty(s1))
                    done1 = 1;
                else {
                    curr1 = pop(s1);
                    val1 = curr1->val;
                    curr1 = curr1->right;
                    done1 = 1;
                }
            }
        }

        // Find next node in REVERSE Inorder traversal. The only
        // difference between above and below loop is, in below loop
        // right subtree is traversed before left subtree
        while (done2 == false) {
            if (curr2 != NULL) {
                push(s2, curr2);
                curr2 = curr2->right;
            }
            else {
                if (isEmpty(s2))
                    done2 = 1;
                else {
                    curr2 = pop(s2);
                    val2 = curr2->val;
                    curr2 = curr2->left;
                    done2 = 1;
                }
            }
        }

        // If we find a pair, then print the pair and return. The first
        // condition makes sure that two same values are not added
        if ((val1 != val2) && (val1 + val2) == target) {
            cout << "Pair Found: " << val1 << "+ " << val2 << " = " << target << endl;
            return true;
        }

        // If sum of current values is smaller,
        // then move to next node in
        // normal inorder traversal
        else if ((val1 + val2) < target)
            done1 = false;

        // If sum of current values is greater,
        // then move to next node in
        // reverse inorder traversal
        else if ((val1 + val2) > target)
            done2 = false;

        // If any of the inorder traversals is
        // over, then there is no pair
        // so return false
        if (val1 >= val2)
            return false;
    }
}

//-------------3. Lca in bst-------------------------

struct node *lca(struct node* root, int n1, int n2)
{
    while (root != NULL)
    {
        // If both n1 and n2 are smaller than root,
        // then LCA lies in left
        if (root->data > n1 && root->data > n2)
            root = root->left;

        // If both n1 and n2 are greater than root,
        // then LCA lies in right
        else if (root->data < n1 && root->data < n2)
            root = root->right;

        else break;
    }
    return root;
}

//-------------------4. Inorder Successor of a given node in a bst--------------------

if (n->right != NULL)
    return minValue(n->right);

struct node* succ = NULL;

// Start from root and search for
// successor down the tree
while (root != NULL) {
    if (n->data < root->data) {
        succ = root;
        root = root->left;
    }
    else if (n->data > root->data)
        root = root->right;
    else
        break;
}

//------------------5. Bst iterator (1st smallest, 2nd, 3rd...... if present)-------------

void pushAllLeft(TreeNode* root) {
    while (root) {
        bst.push(root);
        root = root->left;
    }
}

BSTIterator::BSTIterator(TreeNode *root) {
    pushAllLeft(root);
}

/** @return whether we have a next smallest number */ O(1)
bool BSTIterator::hasNext() {
    return !bst.empty();
}

/** @return the next smallest number */ O(1) average
int BSTIterator::next() {
    TreeNode* curr = bst.top();
    bst.pop();
    pushAllLeft(curr->right);
    return curr->val;
}

//---------------------6. Largest bst in a binary tree - O(n)-------------

class MinMax {
    int min;
    int max;
    boolean isBST;
    int size ;

    MinMax() {
        min = Integer.MAX_VALUE;
        max = Integer.MIN_VALUE;
        isBST = true;
        size = 0;
    }
}

public int largestBST(Node root) {
    MinMax m = largest(root);
    return m.size;
}

private MinMax largest(Node root) {
    //if root is null return min as Integer.MAX and max as Integer.MIN
    if (root == null) {
        return new MinMax();
    }

    //postorder traversal of tree. First visit left and right then
    //use information of left and right to calculate largest BST.
    MinMax leftMinMax = largest(root.left);
    MinMax rightMinMax = largest(root.right);

    MinMax m = new MinMax();

    //if either of left or right subtree says its not BST or the data
    //of this node is not greater/equal than max of left and less than min of right
    //then subtree with this node as root will not be BST.
    //Return false and max size of left and right subtree to parent
    if (leftMinMax.isBST == false || rightMinMax.isBST == false || (leftMinMax.max > root.data || rightMinMax.min <= root.data)) {
        m.isBST = false;
        m.size = Math.max(leftMinMax.size, rightMinMax.size);
        return m;
    }

    //if we reach this point means subtree with this node as root is BST.
    //Set isBST as true. Then set size as size of left + size of right + 1.
    //Set min and max to be returned to parent.
    m.isBST = true;
    m.size = leftMinMax.size + rightMinMax.size + 1;

    //if root.left is null then set root.data as min else
    //take min of left side as min
    m.min = root.left != null ? leftMinMax.min : root.data;

    //if root.right is null then set root.data as max else
    //take max of right side as max.
    m.max = root.right != null ? rightMinMax.max : root.data;

    return m;
}
