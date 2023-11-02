#include "database.h"

Database::Database() {
    db = QSqlDatabase::addDatabase("QPSQL");
}

Database::~Database() {
    closeConnection();
}

void Database::closeConnection() {
//    db.close();
}

bool Database::openConnection() {
    QMap<QString, QString> settings = config.readIniFile("server.ini");
    QString host = settings["HOSTNAME"];
    QString databaseName = settings["DATABASENAME"];
    QString username = settings["USERNAME"];
    QString password = settings["PASSWORD"];

    if (db.isOpen()) {
        qDebug() << "Database connection is already open";
        return true;
    } else {
        db.setHostName(host);
        db.setDatabaseName(databaseName);
        db.setUserName(username);
        db.setPassword(password);

        db.close();
        if (db.open()) {
            qDebug() << "Database connection opened successfully";
            return true;
        } else {
            qDebug() << "Failed to open database connection. Error: " << db.lastError().text();
            createDatabase();
            db.open();
            return false;
        }
    }
}

bool Database::createDatabase() {
    QMap<QString, QString> settings = config.readIniFile("server.ini");
    QString host = settings["HOSTNAME"];
    QString databaseName = settings["DATABASENAME"];
    QString username = settings["USERNAME"];
    QString password = settings["PASSWORD"];

    qDebug() << "Read HOSTNAME from server.ini: " << host;
    qDebug() << "Read DATABASENAME from server.ini: " << databaseName;
    qDebug() << "Read USERNAME from server.ini: " << username;

    db = QSqlDatabase::addDatabase("QPSQL");

    db.setHostName(host);
    db.setDatabaseName("postgres");
    db.setUserName(username);
    db.setPassword(password);

    if (db.open()) {
        QSqlQuery query;
        QString createDbQuery = QString("CREATE DATABASE %1").arg(databaseName);

        qDebug() << "Create DB query: " << createDbQuery;

        if (query.exec(createDbQuery)) {
            qDebug() << "Database created successfully";

            db.close();

            db.setDatabaseName(databaseName);
            if (db.open()) {
                if (createTable()) {
                    qDebug() << "Tables created successfully";
                    return true;
                } else {
                    qDebug() << "Error creating tables";
                }
            } else {
                qDebug() << "Failed to open a connection to the newly created database: " << db.lastError().text();
            }
        } else {
            qDebug() << "Error creating the database:" << query.lastError().text();
        }
    } else {
        qDebug() << "Failed to open a connection to PostgreSQL: " << db.lastError().text();
    }
    return false;
}

bool Database::createTable() {
    if (openConnection()) {
        QSqlQuery query;
        if (query.exec("CREATE TABLE Registration_DATA ("
                       "id_USER SERIAL,"
                       "Email character varying(200) NOT NULL,"
                       "status character varying(100) CHECK (status IN ('active', 'inactive')) default 'active');") &&
            query.exec("CREATE TABLE Authorization_DATA ("
                       "id SERIAL, id_USER integer NOT NULL, "
                       "Password character varying(200) default NULL);") &&
            query.exec("CREATE TABLE History_DATA ("
                       "id_Message SERIAL,id_Sender integer NOT NULL, "
                       "Message text NOT NULL,SEND_ON date Default current_date);") &&
            query.exec("CREATE TABLE History_private_DATA ("
                       "id_Message SERIAL,id_Sender integer NOT NULL, id_Receiver integer NOT NULL, "
                       "Message text NOT NULL,SEND_ON date Default current_date);") &&
            query.exec("CREATE OR REPLACE FUNCTION auto_id() "
                       "RETURNS TRIGGER AS $auto_id$ "
                       "BEGIN "
                       "   INSERT INTO authorization_data (id_user) "
                       "   (SELECT registration_data.id_user FROM registration_data "
                       "   LEFT OUTER JOIN authorization_data ON registration_data.id_user = authorization_data.id_user "
                       "   WHERE authorization_data.id IS NULL); "
                       "   RETURN NEW; "
                       "END; "
                       "$auto_id$ LANGUAGE plpgsql;") &&
            query.exec("CREATE TRIGGER auto_id AFTER INSERT OR UPDATE ON registration_data "
                       "FOR EACH ROW EXECUTE PROCEDURE auto_id();") &&
            query.exec("CREATE OR REPLACE FUNCTION delete_id() RETURNS TRIGGER AS $delete_id_authorization_data$ "
                       "BEGIN "
                       "  DELETE FROM authorization_data "
                       "  WHERE id IN (SELECT authorization_data.id_user "
                       "               FROM authorization_data "
                       "               LEFT OUTER JOIN registration_data ON authorization_data.id_user = registration_data.id_user "
                       "               WHERE registration_data.status='inactive'); "
                       "  RETURN NEW; "
                       "END; "
                       "$delete_id_authorization_data$ LANGUAGE plpgsql;") &&
            query.exec("CREATE TRIGGER delete_id AFTER UPDATE "
                       "ON registration_data FOR EACH ROW EXECUTE PROCEDURE delete_id();") &&
            query.exec("ALTER TABLE registration_data ADD CONSTRAINT id_user PRIMARY KEY (id_user);") &&
            query.exec("ALTER TABLE authorization_data ADD CONSTRAINT id PRIMARY KEY (id);") &&
            query.exec("ALTER TABLE history_data ADD CONSTRAINT id_message PRIMARY KEY (id_message);") &&
            query.exec("ALTER TABLE history_private_data ADD CONSTRAINT id_message PRIMARY KEY (id_message);") &&
            query.exec("ALTER TABLE authorization_data ADD FOREIGN KEY (id_user) REFERENCES registration_data (id_user);") &&
            query.exec("ALTER TABLE history_data ADD FOREIGN KEY (id_sender) REFERENCES registration_data (id_user);") &&
            query.exec("ALTER TABLE history_private_data ADD FOREIGN KEY (id_sender) REFERENCES registration_data (id_user);") &&
            query.exec("ALTER TABLE history_private_data ADD FOREIGN KEY (id_receiver) REFERENCES registration_data (id_user);")) {
            closeConnection();
            return true;
        }
        closeConnection();
    }
    return false;
}


std::vector<std::string> Database::getUserList()
{    std::vector<std::string> userList;
    std::vector<QString> QuserList;
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT email FROM registration_data where status = 'active'");

    for (int row = 0; row < model->rowCount(); ++row) {
        auto email = model->data(model->index(row, 0)).toString();
        QuserList.push_back(email);
    };
    for (const auto &qstr : QuserList) {
        userList.push_back(qstr.toStdString());
    }
    return userList;
}

QString Database::getid(QString Qemail)
{
    QString id_user_sender;
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT id_user FROM registration_data WHERE (email=\'"+Qemail+"\')");
    if (model->rowCount() > 0)
    {        QModelIndex index = model->index(0, 0);
        id_user_sender = model->data(index).toString();
    };
    return id_user_sender;
}

QString Database::getQemail(QString Qid)
{
    QString Qmale;
    QSqlQueryModel *model = new QSqlQueryModel;

    model->setQuery("SELECT email FROM registration_data WHERE (id_user=\'"+Qid+"\')");
    if (model->rowCount() > 0)
    {        QModelIndex index = model->index(0, 0);
        Qmale = model->data(index).toString();
    };
    return Qmale;
}

int Database::checkPassword(std::string email, std::string password)
{
    int j=0;//0 - email не верный
    QString Qemail = QString::fromStdString(email);
    QString Qpassword = QString::fromStdString(password);
    QString id_user;
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT id_user FROM registration_data WHERE (email=\'"+Qemail+"\')");
    if (model->rowCount() > 0)
    {    j=1;
        QModelIndex index = model->index(0, 0);
        id_user = model->data(index).toString();
        model->setQuery("SELECT * FROM authorization_data WHERE (id_user=\'"+id_user+"\') AND (password=\'"+Qpassword+"\') ");
        if (model->rowCount() > 0)
        {
            j=2;
        }
    }
    return j;
}

int addUser(std::string email)
{
    int j=0;
    for (int i = 0; i < email.length(); i++)
    {
        if (email[i] == '@') { j=1; }
    };

    QString Qemail = QString::fromStdString(email);

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT email FROM registration_data WHERE (email=\'"+Qemail+"\')");

    if (model->rowCount() >0) { j=2; }

    return j;
}

void addChatMessage(std::string email, std::string message)
{
    QSqlQuery query;
    QString Qemail = QString::fromStdString(email);
    QString Qmessage = QString::fromStdString(message);
    QString id_user;
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT id_user FROM registration_data WHERE (email=\'"+Qemail+"\')");
    if (model->rowCount() > 0)
    {
        QModelIndex index = model->index(0, 0);
        id_user = model->data(index).toString();
        query.prepare("INSERT INTO history_data (id_sender, message) VALUES (:id_sender,:message)");
        query.bindValue(":id_sender", id_user);
        query.bindValue(":message", Qmessage);
        query.exec();};
}

std::vector<std::string> getUserList()
{    std::vector<std::string> userList;
    std::vector<QString> QuserList;
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT email FROM registration_data where status = 'active'");

    for (int row = 0; row < model->rowCount(); ++row) {
        auto email = model->data(model->index(row, 0)).toString();
        QuserList.push_back(email);
    };
    for (const auto &qstr : QuserList) {
        userList.push_back(qstr.toStdString());
    }
    return userList;
}

void addPrivateMessage(std::string email,std::string email_receiver, std::string message)
{    QSqlQuery query;

    QString id_user_sender;
    QString id_user_receiver;
    QString Qemail = QString::fromStdString(email);
    QString Qemail_receiver = QString::fromStdString(email_receiver);
    QString Qmessage = QString::fromStdString(message);
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT id_user FROM registration_data WHERE (email=\'"+Qemail+"\')");
    if (model->rowCount() > 0)
    {        QModelIndex index = model->index(0, 0);
        id_user_sender = model->data(index).toString();
        model->setQuery("SELECT id_user FROM registration_data WHERE (email=\'"+Qemail_receiver+"\')");

        if (model->rowCount() > 0){
            index = model->index(0, 0);
            id_user_receiver = model->data(index).toString();
            query.prepare("INSERT INTO history_private_data (id_sender,id_receiver, message) VALUES (:id_sender,:id_receiver, :message)");
            query.bindValue(":id_sender", id_user_sender);
            query.bindValue(":id_receiver", id_user_receiver);
            query.bindValue(":message", Qmessage);

            query.exec();};
    }
}

