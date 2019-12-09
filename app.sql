-- 用户表
/**

  username 用户名
  password 密码
  _laster_update_datetime 最后更新时间
  _base_server 服务器域名

 */
CREATE TABLE _user
(
    _id                     integer primary key autoincrement,
    _username               varchar(64),
    _password               varchar(64),
    _userid                 varchar(64),
    _access_token           varchar(256),
    _savepassword           boolean,
    _autologin              boolean,
    _laster_update_datetime integer,
    _base_server            varchar(256)
);


insert into _user(_username, _password, _userid, _access_token, _savepassword, _autologin, _laster_update_datetime,
                  _base_server)
values ('maohuawei', 'maohuawei',
        'MDAxOGxvY2F0aW9uIG1odzgyOC5jb20KMDAxM2lkZW50aWZpZXIga2V5CjAwMTBjaWQgZ2VuID0gMQowMDI4Y2lkIHVzZXJfaWQgPSBAbWFvaHVhd2VpOm1odzgyOC5jb20KMDAxNmNpZCB0eXBlID0gYWNjZXNzCjAwMjFjaWQgbm9uY2UgPSB5V0ZOfndBc0EwVWZSUnY6CjAwMmZzaWduYXR1cmUgoJ01m4zk3zpKwgU-SZTMuoWVGdlFKUWYFsLzYedRKPoK',
        1, 1, 1575623043, 'https://www.mhw828.com');



insert into _user (_username,
                   _password,
                   _userid,
                   _access_token,
                   _savepassword,
                   _autologin,
                   _laster_update_datetime,
                   _base_server)
values ('', '', '', '', 1, 1, 1, '');

-- 房间表

/**

  _avatar 房间头像
  _membercount 房间总人数
  _member_1name 两人对话，房间成员姓名（非自己）

 */
CREATE TABLE _room
(
    _id           integer primary key autoincrement,
    _roomid       varchar(64),
    _name         varchar(256),
    _avatar       varchar(1024),
    _membercount  intger,
    _member_1name varchar(256),
    _base_server  varchar(256),
    _room_version varchar(32)
);


update _room
set _roomid='',
    _name='',
    _avatar='',
    _membercount=1,
    _member_1name='',
    _base_server='',
    _room_version=''
where _roomid = '';


insert into _room ( _roomid ,  _name ,  _avatar ,  _membercount ,  _member_1name ,  _base_server ,  _room_version  )values('!zjeYuzafVAyFSolRjf:mhw828.com','aa','',1,'maohuawei','','5');

insert into _room(_roomid, _name, _avatar, _membercount, _member_1name, _base_server, _room_version)
values ('', '', '', 1, '', '', '');

insert into _room ( _roomid ,  _name ,  _avatar ,  _membercount ,  _member_1name ,  _base_server ,  _room_version  )values('!zjeYuzafVAyFSolRjf:mhw828.com','aa','','1','maohuawei','','5');

insert into _room
    (_roomid, _name, _avatar, _membercount, _member_1name)
values ('', '', '', 1, '');

-- 消息表
/**
  _roomid 房间ID
  _eventid
  -sender 消息发送者
  _me 消息发送者是否为自己

 */
CREATE TABLE _message
(
    _id          integer primary key autoincrement,
    _roomid      varchar(64),
    _eventid     varchar(64),
    _sender      varchar(64),
    _type        varchar(64),
    _datetime    bigint,
    _read        boolean,
    _message     text,
    _me          boolean,
    _base_server varchar(256)
);
insert into _message( _roomid , _eventid , _sender , _type , _datetime , _read , _message , _me , _base_server )values('!zjeYuzafVAyFSolRjf:mhw828.com','$Sd1qcMQ0Dap5SIM62ls-sTgXzQpMShuBIUKjb4JmheI','@maohuawei:mhw828.com','m.text',1575703763 ,\u0001 ,'111',\u0001 ,'https://www.mhw828.com')

insert into _message(_roomid, _eventid, _sender, _type, _datetime, _read, _message, _me, _base_server) values ('','','','',1,false,'',false,'');


insert into _message(_roomid, _eventid, _sender, _type, _datetime, _read, _message, _me)
values ('', '', '', '', 1, 1, '', 1);
-- 房间成员列表

/**

  _online 是否在线
  _member_id 成员ID
  _tvatar 头像

 */

CREATE TABLE _room_member
(
    _id          integer primary key autoincrement,
    _roomid      varchar(64),
    _name        varchar(256),
    _member_id   varchar(256),
    _online      boolean,
    _tvatar      text,
    _base_server varchar(256)
);


insert into _room_member(_roomid, _name, _member_id, _online, _tvatar, _base_server) values ('','','','','','');