/*
  Copyright 2010 Dally Richard
  This file is part of QNetSoul.
  QNetSoul is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  QNetSoul is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with QNetSoul.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "ContactsWriter.h"

ContactsWriter::ContactsWriter(QTreeWidget* tree) : _tree(tree)
{
  setAutoFormatting(true);
}

bool    ContactsWriter::writeFile(QIODevice* device)
{
  setDevice(device);

  writeStartDocument();
  writeDTD("<!DOCTYPE qns>");
  writeStartElement("qns");
  writeAttribute("version", "1.0");

  const int size = this->_tree->topLevelItemCount();
  for (int i = 0; i < size; ++i)
    writeItem(this->_tree->topLevelItem(i));

  writeEndDocument();
  return true;
}

void    ContactsWriter::writeItem(QTreeWidgetItem *item)
{
  const int type = item->data(0, ContactsTree::Type).toInt();

  if (type == ContactsTree::Group)
    {
      bool folded = !this->_tree->isItemExpanded(item);
      writeStartElement("Group");
      writeAttribute("expanded", folded ? "yes" : "no");
      writeTextElement("name", item->text(0));
      for (int i = 0; i < item->childCount(); ++i)
        writeItem(item->child(i));
      writeEndElement();
    }
  else if (type == ContactsTree::Contact)
    {
      bool folded = !this->_tree->isItemExpanded(item);
      writeStartElement("Contact");
      writeAttribute("expanded", folded ? "yes" : "no");

      writeTextElement("alias", item->text(0));
      writeTextElement("login", item->data(0, ContactsTree::Login).toString());
      writeTextElement("promo", item->data(0, ContactsTree::Promo).toString());
      writeEndElement();
    }
}
