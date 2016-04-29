//
//  CollectionViewController.swift
//  Browser
//
//  Created by yangjinxin on 15/10/14.
//  Copyright © 2015年 yangjinxin. All rights reserved.
//

import UIKit

class CollectionViewController: UIViewController,UICollectionViewDataSource,UICollectionViewDelegate {
    @IBOutlet weak var collectView:UICollectionView!
    
    override func viewDidLoad() {
        super.viewDidLoad()

        // Do any additional setup after loading the view.
        self.automaticallyAdjustsScrollViewInsets = false;

    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    /*
    // MARK: - Navigation

    // In a storyboard-based application, you will often want to do a little preparation before navigation
    override func prepareForSegue(segue: UIStoryboardSegue, sender: AnyObject?) {
        // Get the new view controller using segue.destinationViewController.
        // Pass the selected object to the new view controller.
    }
    */
    
    func collectionView(collectionView: UICollectionView, numberOfItemsInSection section: Int) -> Int {
        return 100
    }
    
    func collectionView(collectionView: UICollectionView, cellForItemAtIndexPath indexPath: NSIndexPath) -> UICollectionViewCell {
        //let cell = UICollectionViewCell()
        
        let cell = collectionView.dequeueReusableCellWithReuseIdentifier("sCollectionCell", forIndexPath: indexPath)
        
        cell.contentView.backgroundColor = UIColor.yellowColor()
        
        return cell;
    }
    
    func collectionView(collectionView : UICollectionView,layout collectionViewLayout:UICollectionViewLayout,sizeForItemAtIndexPath indexPath:NSIndexPath) -> CGSize
    {
        
        return CGSizeMake(100, 200)
    }
    
    func collectionView(collectionView: UICollectionView, didSelectItemAtIndexPath indexPath: NSIndexPath) {
        let alamofirVC  = AlamofireViewController()
        self.navigationController?.pushViewController(alamofirVC, animated: false)
    }
    
    
}
