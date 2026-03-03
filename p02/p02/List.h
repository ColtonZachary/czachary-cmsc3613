const int max_list = 5000;   
 
template <class List_entry>
class List {
public:
//  methods of the List ADT
   List();
   int size() const;
   bool full() const;
   bool empty() const;
   void clear();
   void traverse(void (*visit)(List_entry &));
   Error_code retrieve(int position, List_entry &x) const;
   Error_code replace(int position, const List_entry &x);
   Error_code remove(int position, List_entry &x);
   Error_code insert(int position, const List_entry &x);

protected:
//  data members for a contiguous list implementation
   int count;
   List_entry entry[max_list];
};


template <class List_entry>
List<List_entry>::List()
/*  
Post: The List is initialized to be empty. 
*/
{
   count = 0;
}
 
template <class List_entry>
void List<List_entry>::clear()
//  clear:  clear the List.
/*  
Post: The List is cleared. 
*/
{
   count = 0;
}
 
template <class List_entry>
int List<List_entry>::size() const
/*  
Post: The function returns the number of entries in the List. 
*/
{
   return count;
}
 


template <class List_entry>
bool List<List_entry>::empty() const
//  empty: returns non-zero if the List is empty.
/*  
Post: The function returns true or false
according as the List is empty or not. 
*/
{
   return count <= 0;
}
 
template <class List_entry>
bool List<List_entry>::full() const
//  full: returns non-zero if the List is full.
/*  
Post: The function returns true or false
according as the List is full or not. 
*/
{
   return count >= max_list;
}
 
template <class List_entry>
void List<List_entry>::traverse(void (*visit)(List_entry &))
/*  
Post: The action specified by function (*visit) has been performed on every
entry of the List, beginning at position 0 and doing each in turn. 
*/
{
   for (int i = 0; i < count; i++)
      (*visit)(entry[i]);
}
 
template <class List_entry>
Error_code List<List_entry>::insert(int position, const List_entry &x)
/*  
Post: If the List is not full and 0 <= position <= n,
where n is the number of entries in the List,
the function succeeds:
Any entry formerly at
position and all later entries have their
position numbers increased by 1 and
x is inserted at position of the List.
 
Else:
The function fails with a diagnostic error code. 
*/
{
   if (full())
      return overflow;

   if (position < 0 || position > count)
      return range_err;

   for (int i = count - 1; i >= position; i--)
      entry[i + 1] = entry[i];

   entry[position] = x;
   count++;
   return success;
}
 
template <class List_entry>
Error_code List<List_entry>::retrieve(int position, List_entry &x) const
/*  
Post: If the List is not full and 0 <= position < n,
where n is the number of entries in the List,
the function succeeds:
The entry in position is copied to x.
Otherwise the function fails with an error code of range_err. 
*/
{
   if (position < 0 || position >= count) return range_err;
   x = entry[position];
   return success;
}
 
template <class List_entry>
Error_code List<List_entry>::replace(int position, const List_entry &x)
/*  
Post: If 0 <= position < n,
where n is the number of entries in the List,
the function succeeds:
The entry in position is replaced by x,
all other entries remain unchanged.
Otherwise the function fails with an error code of range_err. 
*/
{
   if (position < 0 || position >= count) return range_err;
   entry[position] = x;
   return success;
}
 

template <class List_entry>
Error_code List<List_entry>::remove(int position, List_entry &x)
/*  
Post: If 0 <= position < n,
where n is the number of entries in the List,
the function succeeds:
The entry in position is removed
from the List, and the entries in all later positions
have their position numbers decreased by 1.
The parameter x records a copy of
the entry formerly in position.
Otherwise the function fails with a diagnostic error code. 
*/
{
   if (count == 0) return underflow;
   if (position < 0 || position >= count) return range_err;

   x = entry[position];
   count--;
   while (position < count) {
      entry[position] = entry[position + 1];
      position++;
   }
   return success;
}
