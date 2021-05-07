#include "TreeNode.hpp"

TreeNode::TreeNode(TreeNode* parent, const QVector<QVariant>& columns) :
	_columns(columns),
	_parent(parent)
{
}

TreeNode::~TreeNode()
{
	qDeleteAll(_rows);
}

TreeNode* TreeNode::parent() const
{
	return _parent;
}

void TreeNode::appendRow(TreeNode* child)
{
	_rows.append(child);
}

TreeNode* TreeNode::rowAt(int row) const
{
	if (row < 0 || row >= columnCount())
	{
		return nullptr;
	}

	return _rows.at(row);
}

int TreeNode::rowCount() const
{
	return _rows.size();
}

int TreeNode::currentRow() const
{
	return _parent ?
		_parent->_rows.indexOf(const_cast<TreeNode*>(this)) :
		0;
}

int TreeNode::columnCount() const
{
	return _columns.size();
}

QVariant TreeNode::data(int column) const
{
	if (column < 0 || column >= columnCount())
	{
		return QVariant();
	}

	return _columns.at(column);
}
