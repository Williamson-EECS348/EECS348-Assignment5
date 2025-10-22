#pragma once

typedef struct {
    char* category;
    char* subject;
    char* date;
} EmailNode;

EmailNode* EmailNode_create(const char* category, const char* subject, const char* date);
void EmailNode_destroy(EmailNode* node);
int EmailNode_compare(const EmailNode* a, const EmailNode* b);
int EmailNode_compareGT(const EmailNode* a, const EmailNode* b);
void EmailNode_printNode(const EmailNode* node);