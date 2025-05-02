#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

struct node {
    std::string name;
    std::vector<node> children;
};

void add_path(node* tree_root, const std::vector<std::string>& path_parts);
int get_node_id(const std::vector<node>& array, const std::string& element);
void print_tree(const node& tree_root, unsigned int depth = 0);
void sort_tree(node& tree_root);

int main() {
    int n;
    std::cin >> n;
    std::cin.ignore();
    node tree;
    tree.name = ""; 
    for (int i = 0; i < n; ++i) {
        std::vector<std::string> path_parts;
        std::string part;
        char ch;
        while ((ch = std::cin.get()) != '\n') {
            if (ch == '\\') {
                path_parts.push_back(part);
                part.clear();
                continue;
            }
            part.push_back(ch);
        }
        if (!part.empty()) {
            path_parts.push_back(part);
        }
        add_path(&tree, path_parts);
    }

    sort_tree(tree);
    print_tree(tree);

    return 0;
}

void add_path(node* tree_root, const std::vector<std::string>& path_parts) {
    node* cur_node = tree_root;
    for (std::string part : path_parts) {
        int node_id = get_node_id(cur_node->children, part);
        if (node_id == -1) {
            node new_part;
            new_part.name = part;
            cur_node->children.push_back(new_part);
            cur_node = &cur_node->children.back();
        }
        else cur_node = &cur_node->children[node_id];
    }
}

int get_node_id(const std::vector<node>& array, const std::string& element) {
    for (int i = 0; i < array.size(); ++i)
        if (element == array[i].name)
            return i;
    return -1;
}

void print_tree(const node& tree_root, unsigned int depth) {
    for (int i = 0; i < tree_root.children.size(); ++i) {
        std::cout << std::string(depth, ' ') << tree_root.children[i].name << std::endl;
        print_tree(tree_root.children[i], depth + 1);
    }
}

void sort_tree(node& tree_root) {
    std::sort(tree_root.children.begin(), tree_root.children.end(), [](const node& a, const node& b) {
        return a.name < b.name;
    });
    for (node& child : tree_root.children)
        sort_tree(child);
}