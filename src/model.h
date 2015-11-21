#ifndef MODEL_H
#define MODEL_H

class model {

public:
	model(backend& db) : db(db) {};
	virtual void save() = 0;
	virtual void load() = 0;

protected:
	backend& db;

};

#endif /* MODEL_H */

