#include "TreeModel.hpp"
#include "TreeNode.hpp"

inline TreeNode* indexToNode(const QModelIndex& index)
{
	return static_cast<TreeNode*>(index.internalPointer());
}

TreeModel::TreeModel(QObject* parent) :
	QAbstractItemModel(parent)
{
	_root = new TreeNode(nullptr, {"Column 0", "Column 1", "Column 2"});

	auto alpha = new TreeNode(_root, { "Row 0" });
	alpha->appendRow(new TreeNode(alpha, {"a", "b", "c" }));

	auto bravo = new TreeNode(_root, {"Row 1" });
	bravo->appendRow(new TreeNode(bravo, {"d", "e", "f" }));

	_root->appendRow(alpha);
	_root->appendRow(bravo);
}

TreeModel::~TreeModel()
{
	delete _root;
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (orientation != Qt::Horizontal || role != Qt::DisplayRole)
	{
		return QVariant();
	}

	 return _root->data(section);
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex& parentIndex) const
{
	if (!hasIndex(row, column, parentIndex))
	{
		return QModelIndex();
	}

	TreeNode* parent = parentIndex.isValid() ? indexToNode(parentIndex) : _root;

	TreeNode* child = parent->rowAt(row);

	return child ? createIndex(row, column, child) : QModelIndex();
}

QModelIndex TreeModel::parent(const QModelIndex& childIndex) const
{
	if (!childIndex.isValid())
	{
		return QModelIndex();
	}

	TreeNode* child = indexToNode(childIndex);
	TreeNode* parent = child->parent();

	return parent == _root ?
		QModelIndex() :
		createIndex(parent->currentRow(), 0, parent);
}

int TreeModel::rowCount(const QModelIndex& parentIndex) const
{
	if (parentIndex.column() > 0)
	{
		return 0;
	}

	return parentIndex.isValid() ?
		indexToNode(parentIndex)->rowCount() :
		_root->rowCount();
}

int TreeModel::columnCount(const QModelIndex& parentIndex) const
{
	return parentIndex.isValid() ?
		std::max(
			_root->columnCount(),
			indexToNode(parentIndex)->columnCount()) :
		_root->columnCount();
}

QVariant TreeModel::data(const QModelIndex& index, int role) const
{
	if (!index.isValid() || role != Qt::DisplayRole)
	{
		return QVariant();
	}

	return indexToNode(index)->data(index.column());
}
