void EnsureEqual(const string& left, const string& right){
	if (left != right){
		string err = left + " != " + right;
		throw runtime_error(err);
	}
}
