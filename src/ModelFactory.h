#include "any.h"
#include "backend.h"
#include "model.h"
#include "model/models.h"

class ModelFactory {
public:
	enum ModelType {
		AppSettings,
		Database,
		DatabaseType,
		DatabaseUser,
		Dns,
		Domain,
		FtpAccount,
		Mailbox,
		Shell,
		Subdomain,
		User,
		UserDbUserDb,
		Vhost,
		Queue,
		DomainAlias
	};

	static std::unique_ptr<model> createModel(ModelType modeltype, backend& db, std::map<std::string,any> primary) {
		if(primary.size() > 0)
		{
			switch (modeltype)
			{
				case AppSettings : return std::make_unique<app_settings>(db, (std::string)primary["key"].string);
				case Database : return std::make_unique<database>(db, primary["name"].string);
				case DatabaseType : return std::make_unique<database_type>(db, primary["name"].string);
				case DatabaseUser : return std::make_unique<database_user>(db, primary["name"].string);
				case Dns : return std::make_unique<dns>(db, primary["id"].integer);
				case Domain : return std::make_unique<domain>(db, primary["name"].string);
				case FtpAccount : return std::make_unique<ftp_account>(db, primary["id"].integer);
				case Mailbox : return std::make_unique<mailbox>(db, primary["id"].integer);
				case Shell : return std::make_unique<shell>(db, primary["id"].integer);
				case Subdomain : return std::make_unique<subdomain>(db, primary["name"].string, primary["domain_name"].string);
				case User : return std::make_unique<user>(db, primary["uid"].integer);
				case UserDbUserDb : return std::make_unique<user_dbuser_db>(db, primary["username"].string, primary["name"].string);
				case Vhost : return std::make_unique<vhost>(db, primary["id"].integer);
				case Queue : return std::make_unique<queue>(db, primary["qid"].integer);
				case DomainAlias : return std::make_unique<domain_alias>(db, primary["id"].integer);
			}
			throw "invalid model type.";
		}
		else {
			switch (modeltype)
			{
				case AppSettings : return std::make_unique<app_settings>(db);
				case Database : return std::make_unique<database>(db);
				case DatabaseType : return std::make_unique<database_type>(db);
				case DatabaseUser : return std::make_unique<database_user>(db);
				case Dns : return std::make_unique<dns>(db);
				case Domain : return std::make_unique<domain>(db);
				case FtpAccount : return std::make_unique<ftp_account>(db);
				case Mailbox : return std::make_unique<mailbox>(db);
				case Shell : return std::make_unique<shell>(db);
				case Subdomain : return std::make_unique<subdomain>(db);
				case User : return std::make_unique<user>(db);
				case UserDbUserDb : return std::make_unique<user_dbuser_db>(db);
				case Vhost : return std::make_unique<vhost>(db);
				case Queue : return std::make_unique<queue>(db);
				case DomainAlias : return std::make_unique<domain_alias>(db);
			}
			throw "invalid model type.";
		}
	}
};