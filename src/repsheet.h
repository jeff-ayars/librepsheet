#ifndef __REPSHEET_H
#define __REPSHEET_H

#define TRUE 1
#define FALSE 0

typedef struct repsheet_rule_t {
  char *part;
  char *location;
  char *field;
  char *error;
} repsheet_rule_t;

redisContext *get_redis_context(const char *host, int port, int timeout);

void increment_rule_count(redisContext *context, const char *actor, char *rule);

void mark_actor(redisContext *context, const char *actor);
void blacklist_actor(redisContext *context, const char *actor);
void whitelist_actor(redisContext *context, const char *actor);

int is_on_repsheet(redisContext *context, const char *actor);
int is_blacklisted(redisContext *context, const char *actor);
int is_whitelisted(redisContext *context, const char *actor);
int is_historical_offender(redisContext *context, const char *actor);

void expire(redisContext *context, const char *actor, char *label, int expiry);
void blacklist_and_expire(redisContext *context, const char *actor, int expiry, char *reason);

void record(redisContext *context, char *timestamp, const char *user_agent,
            const char *http_method, char *uri, char *arguments, int redis_max_length,
            int redis_expiry, const char *actor);

const char *remote_address(char *connected_address, const char *xff_header);

int modsecurity_total(const char *waf_score);
void process_mod_security_headers(const char *waf_events, char *events[]);
int matches(const char *waf_events);

repsheet_rule_t process_rule(char *rule_string);

#endif