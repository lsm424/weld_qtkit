#include "mysql_pool.h"
#include "easylogging++.h"


MysqlPool* MysqlPool::mysqlpool_object = NULL;
QMutex MysqlPool::objectlock;
QMutex MysqlPool::poollock;

MysqlPool::MysqlPool() {}

/*
 *配置数据库参数
 */
void MysqlPool::setParameter( const char*   mysqlhost,
                              const char*   mysqluser,
                              const char*   mysqlpwd,
                              const char*   databasename,
                              unsigned int  port,
                              const char*   socket,
                              unsigned long client_flag,
                              unsigned int  max_connect ) {
  _mysqlhost    = mysqlhost;
  _mysqluser    = mysqluser;
  _mysqlpwd     = mysqlpwd;
  _databasename = databasename;
  _port         = port;
  _socket       = socket;
  _client_flag  = client_flag;
  MAX_CONNECT   = max_connect;
}

/*
 *有参的单例函数，用于第一次获取连接池对象，初始化数据库信息。
 */
MysqlPool* MysqlPool::Instance() {
  if (mysqlpool_object == NULL) {
    objectlock.lock();
    if (mysqlpool_object == NULL) {
      mysqlpool_object = new MysqlPool();
    }
    objectlock.unlock();
  }
  return mysqlpool_object;
}

/*
 *创建一个连接对象
 */
MYSQL* MysqlPool::createOneConnect() {
  MYSQL* conn = NULL;
  conn = mysql_init(conn);
  if (conn != NULL) {
    if (mysql_real_connect(conn,
                          _mysqlhost,
                          _mysqluser,
                          _mysqlpwd,
                          _databasename,
                          _port,
                          _socket,
                          _client_flag)) {
      connect_count++;
      return conn;
    } else {
      LOG(ERROR) << "connect mysql failed, " << mysql_error(conn) << std::endl;
      return NULL;
    }
  } else {
    LOG(ERROR) << "init mysql failed"  ;
    return NULL;
  }
}


/*
 *获取连接对象，如果连接池中有连接，就取用;没有，就重新创建一个连接对象。
 *同时注意到MySQL的连接的时效性，即在连接队列中,连接对象在超过一定的时间后没有进行操作，
 *MySQL会自动关闭连接，当然还有其他原因，比如：网络不稳定，带来的连接中断。
 *所以在获取连接对象前，需要先判断连接池中连接对象是否有效。
 *考虑到数据库同时建立的连接数量有限制，在创建新连接需提前判断当前开启的连接数不超过设定值。
 */
MYSQL* MysqlPool::getOneConnect() {
    poollock.lock();
    MYSQL *conn = NULL;

    while (!mysqlpool.isEmpty() && mysql_ping(mysqlpool.front())) {
      mysql_close(mysqlpool.front());
      mysqlpool.pop_front();
      connect_count--;
    }
    if (!mysqlpool.isEmpty()) {
      conn = mysqlpool.front();
      mysqlpool.pop_front();
    } else {
      conn = createOneConnect();
    }

    poollock.unlock();
    return conn;
}

/*
 *将有效的链接对象放回链接池队列中，以待下次的取用。
 */
void MysqlPool::close(MYSQL* conn) {
  if (conn != NULL) {
    poollock.lock();
    mysqlpool.push_back(conn);
    poollock.unlock();
  }
}
/*
 * sql语句执行函数，并返回结果，没有结果的SQL语句返回空结果，
 * 每次执行SQL语句都会先去连接队列中去一个连接对象，
 * 执行完SQL语句，就把连接对象放回连接池队列中。
 * 返回对象用map主要考虑，用户可以通过数据库字段，直接获得查询的字。
 * 例如：m["字段"][index]。
 */
QVector<QVector<QVariant>>  MysqlPool::executeSql(const char* sql) {
    QVector<QVector<QVariant>> results;
    MYSQL* conn = getOneConnect();
    if (!conn) {
        LOG(ERROR) << "connect mysql failed, " << mysql_error(conn) << std::endl;
        return results;
    }
    if (mysql_query(conn,sql) == 0) {
        MYSQL_RES *res = mysql_store_result(conn);
        if (res) {
            int dwColNum = mysql_num_fields(res);
            MYSQL_ROW row;
            while ((row = mysql_fetch_row(res))) {
                unsigned int i = 0;
                QVector<QVariant> qrow;
                for (int i = 0; i < dwColNum; i++) {
                    qrow.push_back(QVariant(row[i++]));
                }
                results.push_back(qrow);
            }
        }
        mysql_free_result(res);
    } else if (mysql_field_count(conn) != 0) {
        LOG(ERROR) << "connect mysql failed, " << mysql_error(conn) << std::endl;
    }

    close(conn);
    return results;
}
/*
 * 析构函数，将连接池队列中的连接全部关闭
 */
MysqlPool::~MysqlPool() {
  while (!mysqlpool.isEmpty()) {
    mysql_close(mysqlpool.front());
    mysqlpool.pop_front();
    connect_count--;
  }
}
