//
template <class ContainerT, class Val1T, class Val2T>
bool multiThreadingSearch(
    ContainerT container,                     // search area
    Val1T src_args,                           // arg needed in function body
    bool (*check)(Val1T src_args, Val2T item) // functoin we want to call for each item in search area
);