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
		Vhost
	};

	static std::unique_ptr<model> createModel(ModelType modeltype, backend& db, std::vector<any> primary) {
		if(primary.size() > 0)
		{
			switch (modeltype)
			{
				case AppSettings : return std::make_unique<app_settings>(db, (std::string)primary[0].string);
				case Database : return std::make_unique<database>(db, primary[0].string);
				case DatabaseType : return std::make_unique<database_type>(db, primary[0].string);
				case DatabaseUser : return std::make_unique<database_user>(db, primary[0].string);
				case Dns : return std::make_unique<dns>(db, primary[0].integer);
				case Domain : return std::make_unique<domain>(db, primary[0].string);
				case FtpAccount : return std::make_unique<ftp_account>(db, primary[0].string);
				case Mailbox : return std::make_unique<mailbox>(db, primary[0].integer);
				case Shell : return std::make_unique<shell>(db, primary[0].integer);
				case Subdomain : return std::make_unique<subdomain>(db, primary[0].string, primary[1].string);
				case User : return std::make_unique<user>(db, primary[0].integer);
				case UserDbUserDb : return std::make_unique<user_dbuser_db>(db, primary[0].string, primary[2].string);
				case Vhost : return std::make_unique<vhost>(db, primary[0].integer);
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
			}
			throw "invalid model type.";
		}
	}
};