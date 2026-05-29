from github import Github
import os

def main():
    token = os.getenv("GITHUB_TOKEN")
    if not token:
        print("❌ 找不到 GITHUB_TOKEN")
        return
    
    g = Github(token)
    
    # 获取当前仓库（GitHub Actions 会自动提供）
    repo_name = os.getenv("GITHUB_REPOSITORY")
    if not repo_name:
        print("❌ 找不到 GITHUB_REPOSITORY")
        return
    
    repo = g.get_repo(repo_name)
    print(f"📁 仓库: {repo.full_name}")
    
    # 获取所有开放的 PR
    pulls = repo.get_pulls(state="open")
    print(f"📋 找到 {pulls.totalCount} 个开放 PR")
    
    for pr in pulls:
        print(f"\n🔍 处理 PR #{pr.number}: {pr.title}")
        
        # 获取当前标签
        current_labels = [label.name for label in pr.get_labels()]
        print(f"   当前标签: {current_labels if current_labels else '无'}")
        
        # 检查是否已批准
        reviews = pr.get_reviews()
        is_approved = any(review.state == "APPROVED" for review in reviews)
        print(f"   已批准: {is_approved}")
        
        # 根据状态打标签
        if is_approved:
            if "awaiting-merge" not in current_labels:
                pr.add_to_labels("awaiting-merge")
                print("   ✅ 添加标签: awaiting-merge")
            if "awaiting-review" in current_labels:
                pr.remove_from_labels("awaiting-review")
                print("   🗑️ 移除标签: awaiting-review")
        else:
            if "awaiting-review" not in current_labels:
                pr.add_to_labels("awaiting-review")
                print("   ✅ 添加标签: awaiting-review")
            if "awaiting-merge" in current_labels:
                pr.remove_from_labels("awaiting-merge")
                print("   🗑️ 移除标签: awaiting-merge")

if __name__ == "__main__":
    main()