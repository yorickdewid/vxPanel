#ifndef MODEL_H
#define MODEL_H

class model {

public:
	model(backend& db) :
		db(db),
		saved(false)
	{};
	virtual void save() = 0;
	virtual void load() = 0;
	virtual bool update(std::string field) = 0;
	virtual bool m_delete() = 0;

	bool get_saved(){ return this->saved; };

protected:
	backend& db;
	bool saved;

};

#endif /* MODEL_H */

