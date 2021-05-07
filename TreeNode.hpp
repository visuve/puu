#pragma once

#include <QVariant>
#include <QVector>

class TreeNode
{
public:
	explicit TreeNode(TreeNode* parent, const QVector<QVariant>& columns);
	~TreeNode();

	TreeNode* parent() const;

	void appendRow(TreeNode *child);
	TreeNode* rowAt(int row) const;
	int rowCount() const;
	int currentRow() const;

	int columnCount() const;
	QVariant data(int column) const;

private:
	TreeNode* _parent;
	QVector<TreeNode*> _rows;
	QVector<QVariant> _columns;
};
